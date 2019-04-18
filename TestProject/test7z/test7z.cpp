// test7z.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Initguid.h>
#include "FileStreams.h"
#include "7zTypes.h"
#include "Defs.h"
#include "IArchive.h"
#include "MyCom.h"
#include "IPassword.h"
#include "MyVector.h"
#include "MyString.h"
#include "PropVariant.h"
#include "filename.h"
#include "filedir.h"
#include "FileFind.h"

using namespace NWindows;
using namespace NFile;
using namespace NDir;
template<typename T>
void Print(T &&t)
{

}
static const char * const kTestingString = "Testing     ";
static const char * const kExtractingString = "Extracting  ";
static const char * const kSkippingString = "Skipping    ";

static const char * const kUnsupportedMethod = "Unsupported Method";
static const char * const kCRCFailed = "CRC Failed";
static const char * const kDataError = "Data Error";
static const char * const kUnavailableData = "Unavailable data";
static const char * const kUnexpectedEnd = "Unexpected end of data";
static const char * const kDataAfterEnd = "There are some data after the end of the payload data";
static const char * const kIsNotArc = "Is not archive";
static const char * const kHeadersError = "Headers Error";


DEFINE_GUID(CLSID_CFormat7z,
	0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x07, 0x00, 0x00);
extern "C"
{
	typedef HRESULT(WINAPI *Func_CreateObject)(const GUID *clsID, const GUID *iid, void **outObject);

	typedef UInt32(WINAPI *Func_IsArc)(const Byte *p, size_t size);
	typedef HRESULT(WINAPI *Func_GetIsArc)(UInt32 formatIndex, Func_IsArc *isArc);

	typedef HRESULT(WINAPI *Func_GetNumberOfFormats)(UInt32 *numFormats);
	typedef HRESULT(WINAPI *Func_GetHandlerProperty)(PROPID propID, PROPVARIANT *value);
	typedef HRESULT(WINAPI *Func_GetHandlerProperty2)(UInt32 index, PROPID propID, PROPVARIANT *value);

	typedef HRESULT(WINAPI *Func_SetCaseSensitive)(Int32 caseSensitive);
	typedef HRESULT(WINAPI *Func_SetLargePageMode)();

	//typedef IOutArchive * (*Func_CreateOutArchive)();
	//typedef IInArchive * (*Func_CreateInArchive)();
}
inline bool ConvertPropVariantToUInt64(const PROPVARIANT &prop, UInt64 &value)
{
	switch (prop.vt)
	{
	case VT_UI8: value = (UInt64)prop.uhVal.QuadPart; return true;
	case VT_UI4: value = prop.ulVal; return true;
	case VT_UI2: value = prop.uiVal; return true;
	case VT_UI1: value = prop.bVal; return true;
	case VT_EMPTY: return false;
	default: throw 151199;
	}
}


struct CDirItem
{
	UInt64 Size;
	FILETIME CTime;
	FILETIME ATime;
	FILETIME MTime;
	UString Name;
	FString FullPath;
	UInt32 Attrib;

	bool isDir() const { return (Attrib & FILE_ATTRIBUTE_DIRECTORY) != 0; }
};
class CArchiveUpdateCallback :
	public IArchiveUpdateCallback2,
	public ICryptoGetTextPassword2,
	public CMyUnknownImp
{
public:
	MY_UNKNOWN_IMP2(IArchiveUpdateCallback2, ICryptoGetTextPassword2)

		// IProgress
		STDMETHOD(SetTotal)(UInt64 size);
	STDMETHOD(SetCompleted)(const UInt64 *completeValue);

	// IUpdateCallback2
	STDMETHOD(GetUpdateItemInfo)(UInt32 index,
		Int32 *newData, Int32 *newProperties, UInt32 *indexInArchive);
	STDMETHOD(GetProperty)(UInt32 index, PROPID propID, PROPVARIANT *value);
	STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **inStream);
	STDMETHOD(SetOperationResult)(Int32 operationResult);
	STDMETHOD(GetVolumeSize)(UInt32 index, UInt64 *size);
	STDMETHOD(GetVolumeStream)(UInt32 index, ISequentialOutStream **volumeStream);

	STDMETHOD(CryptoGetTextPassword2)(Int32 *passwordIsDefined, BSTR *password);

public:
	CRecordVector<UInt64> VolumesSizes;
	UString VolName;
	UString VolExt;

	FString DirPrefix;
	const CObjectVector<CDirItem> *DirItems;

	bool PasswordIsDefined;
	UString Password;
	bool AskPassword;

	bool m_NeedBeClosed;

	FStringVector FailedFiles;
	CRecordVector<HRESULT> FailedCodes;

	CArchiveUpdateCallback() : PasswordIsDefined(false), AskPassword(false), DirItems(0) {};

	~CArchiveUpdateCallback() { Finilize(); }
	HRESULT Finilize();

	void Init(const CObjectVector<CDirItem> *dirItems)
	{
		DirItems = dirItems;
		m_NeedBeClosed = false;
		FailedFiles.Clear();
		FailedCodes.Clear();
	}
};

STDMETHODIMP CArchiveUpdateCallback::SetTotal(UInt64 /* size */)
{
	return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::SetCompleted(const UInt64 * /* completeValue */)
{
	return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::GetUpdateItemInfo(UInt32 /* index */,
	Int32 *newData, Int32 *newProperties, UInt32 *indexInArchive)
{
	if (newData)
		*newData = BoolToInt(true);
	if (newProperties)
		*newProperties = BoolToInt(true);
	if (indexInArchive)
		*indexInArchive = (UInt32)(Int32)-1;
	return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::GetProperty(UInt32 index, PROPID propID, PROPVARIANT *value)
{
	NWindows::NCOM::CPropVariant prop;

	if (propID == kpidIsAnti)
	{
		prop = false;
		prop.Detach(value);
		return S_OK;
	}

	{
		const CDirItem &dirItem = (*DirItems)[index];
		switch (propID)
		{
		case kpidPath:  prop = dirItem.Name; break;
		case kpidIsDir:  prop = dirItem.isDir(); break;
		case kpidSize:  prop = dirItem.Size; break;
		case kpidAttrib:  prop = dirItem.Attrib; break;
		case kpidCTime:  prop = dirItem.CTime; break;
		case kpidATime:  prop = dirItem.ATime; break;
		case kpidMTime:  prop = dirItem.MTime; break;
		}
	}
	prop.Detach(value);
	return S_OK;
}
static void Print(const char *s)
{
	fputs(s, stdout);
}
static void PrintNewLine()
{
	Print("\n");
}
HRESULT CArchiveUpdateCallback::Finilize()
{
	if (m_NeedBeClosed)
	{
		PrintNewLine();
		m_NeedBeClosed = false;
	}
	return S_OK;
}
static void Print(const wchar_t *s)
{
	//Print(UString(s));
}
static const wchar_t * const kEmptyFileAlias = L"[Content]";
static void GetStream2(const wchar_t *name)
{
	Print("Compressing  ");
	if (name[0] == 0)
		name = kEmptyFileAlias;
	Print(name);
}

STDMETHODIMP CArchiveUpdateCallback::GetStream(UInt32 index, ISequentialInStream **inStream)
{
	RINOK(Finilize());

	const CDirItem &dirItem = (*DirItems)[index];
	GetStream2(dirItem.Name);

	if (dirItem.isDir())
		return S_OK;

	{
		CInFileStream *inStreamSpec = new CInFileStream;
		CMyComPtr<ISequentialInStream> inStreamLoc(inStreamSpec);
		FString path = DirPrefix + dirItem.FullPath;
		if (!inStreamSpec->Open(path))
		{
			DWORD sysError = ::GetLastError();
			FailedCodes.Add(sysError);
			FailedFiles.Add(path);
			// if (systemError == ERROR_SHARING_VIOLATION)
			{
				PrintNewLine();
				//PrintError("WARNING: can't open file");
				// Print(NError::MyFormatMessageW(systemError));
				return S_FALSE;
			}
			// return sysError;
		}
		*inStream = inStreamLoc.Detach();
	}
	return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::SetOperationResult(Int32 /* operationResult */)
{
	m_NeedBeClosed = true;
	return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::GetVolumeSize(UInt32 index, UInt64 *size)
{
	if (VolumesSizes.Size() == 0)
		return S_FALSE;
	if (index >= (UInt32)VolumesSizes.Size())
		index = VolumesSizes.Size() - 1;
	*size = VolumesSizes[index];
	return S_OK;
}
#define CONVERT_INT_TO_STR(charType, tempSize) \
  unsigned char temp[tempSize]; unsigned i = 0; \
  while (val >= 10) { temp[i++] = (unsigned char)('0' + (unsigned)(val % 10)); val /= 10; } \
  *s++ = (charType)('0' + (unsigned)val); \
  while (i != 0) { i--; *s++ = temp[i]; } \
  *s = 0;

static void ConvertUInt32ToString(UInt32 val, wchar_t *s) throw()
{
	CONVERT_INT_TO_STR(wchar_t, 16);
}
void ConvertUInt32ToString(UInt32 val, char *s) throw()
{
	CONVERT_INT_TO_STR(char, 16);
}
STDMETHODIMP CArchiveUpdateCallback::GetVolumeStream(UInt32 index, ISequentialOutStream **volumeStream)
{
	wchar_t temp[16];
	ConvertUInt32ToString(index + 1, temp);
	UString res = temp;
	while (res.Len() < 2)
		res.InsertAtFront(L'0');
	UString fileName = VolName;
	fileName += '.';
	fileName += res;
	fileName += VolExt;
	COutFileStream *streamSpec = new COutFileStream;
	CMyComPtr<ISequentialOutStream> streamLoc(streamSpec);
	if (!streamSpec->Create(us2fs(fileName), false))
		return ::GetLastError();
	*volumeStream = streamLoc.Detach();
	return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::CryptoGetTextPassword2(Int32 *passwordIsDefined, BSTR *password)
{
	if (!PasswordIsDefined)
	{
		if (AskPassword)
		{
			// You can ask real password here from user
			// Password = GetPassword(OutStream);
			// PasswordIsDefined = true;
			//PrintError("Password is not defined");
			return E_ABORT;
		}
	}
	*passwordIsDefined = BoolToInt(PasswordIsDefined);
	return StringToBstr(Password, password);
}


class CArchiveOpenCallback :
	public IArchiveOpenCallback,
	public ICryptoGetTextPassword,
	public CMyUnknownImp
{
public:
	MY_UNKNOWN_IMP1(ICryptoGetTextPassword)

		STDMETHOD(SetTotal)(const UInt64 *files, const UInt64 *bytes);
	STDMETHOD(SetCompleted)(const UInt64 *files, const UInt64 *bytes);

	STDMETHOD(CryptoGetTextPassword)(BSTR *password);

	bool PasswordIsDefined;
	UString Password;

	CArchiveOpenCallback() : PasswordIsDefined(false) {}
};

STDMETHODIMP CArchiveOpenCallback::SetTotal(const UInt64 * /* files */, const UInt64 * /* bytes */)
{
	return S_OK;
}

STDMETHODIMP CArchiveOpenCallback::SetCompleted(const UInt64 * /* files */, const UInt64 * /* bytes */)
{
	return S_OK;
}

STDMETHODIMP CArchiveOpenCallback::CryptoGetTextPassword(BSTR *password)
{
	if (!PasswordIsDefined)
	{
		// You can ask real password here from user
		// Password = GetPassword(OutStream);
		// PasswordIsDefined = true;
		//PrintError("Password is not defined");
		return E_ABORT;
	}
	return StringToBstr(Password, password);
}

class CArchiveExtractCallback :
	public IArchiveExtractCallback,
	public ICryptoGetTextPassword,
	public CMyUnknownImp
{
public:
	MY_UNKNOWN_IMP1(ICryptoGetTextPassword)

		// IProgress
		STDMETHOD(SetTotal)(UInt64 size);
	STDMETHOD(SetCompleted)(const UInt64 *completeValue);

	// IArchiveExtractCallback
	STDMETHOD(GetStream)(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode);
	STDMETHOD(PrepareOperation)(Int32 askExtractMode);
	STDMETHOD(SetOperationResult)(Int32 resultEOperationResult);

	// ICryptoGetTextPassword
	STDMETHOD(CryptoGetTextPassword)(BSTR *aPassword);
private:
	CMyComPtr<IInArchive> _archiveHandler;
	FString _directoryPath;  // Output directory
	UString _filePath;       // name inside arcvhive
	FString _diskFilePath;   // full path to file on disk
	bool _extractMode;
	struct CProcessedFileInfo
	{
		FILETIME MTime;
		UInt32 Attrib;
		bool isDir;
		bool AttribDefined;
		bool MTimeDefined;
	} _processedFileInfo;

	COutFileStream *_outFileStreamSpec;
	CMyComPtr<ISequentialOutStream> _outFileStream;

public:
	void Init(IInArchive *archiveHandler, const FString &directoryPath);

	UInt64 NumErrors;
	bool PasswordIsDefined;
	UString Password;

	CArchiveExtractCallback() : PasswordIsDefined(false) {}
	UInt64 total = 0;
};

void CArchiveExtractCallback::Init(IInArchive *archiveHandler, const FString &directoryPath)
{
	NumErrors = 0;
	_archiveHandler = archiveHandler;
	_directoryPath = directoryPath;
	NWindows::NFile::NName::NormalizeDirPathPrefix(_directoryPath);
}

STDMETHODIMP CArchiveExtractCallback::SetTotal(UInt64 size)
{
	total = size;
	return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::SetCompleted(const UInt64 *  completeValue)
{
	printf("Completed %lld\n", *completeValue * 100 / total);
	return S_OK;
}
static HRESULT IsArchiveItemProp(IInArchive *archive, UInt32 index, PROPID propID, bool &result)
{
	NWindows::NCOM::CPropVariant prop;
	RINOK(archive->GetProperty(index, propID, &prop));
	if (prop.vt == VT_BOOL)
		result = VARIANT_BOOLToBool(prop.boolVal);
	else if (prop.vt == VT_EMPTY)
		result = false;
	else
		return E_FAIL;
	return S_OK;
}

static HRESULT IsArchiveItemFolder(IInArchive *archive, UInt32 index, bool &result)
{
	return IsArchiveItemProp(archive, index, kpidIsDir, result);
}
STDMETHODIMP CArchiveExtractCallback::GetStream(UInt32 index,
	ISequentialOutStream **outStream, Int32 askExtractMode)
{
	*outStream = 0;
	_outFileStream.Release();

	{
		// Get Name
		NWindows::NCOM::CPropVariant prop;
		RINOK(_archiveHandler->GetProperty(index, kpidPath, &prop));

		UString fullPath;
		if (prop.vt == VT_EMPTY)
			fullPath = kEmptyFileAlias;
		else
		{
			if (prop.vt != VT_BSTR)
				return E_FAIL;
			fullPath = prop.bstrVal;
		}
		_filePath = fullPath;
	}

	if (askExtractMode != NArchive::NExtract::NAskMode::kExtract)
		return S_OK;

	{
		// Get Attrib
		NWindows::NCOM::CPropVariant prop;
		RINOK(_archiveHandler->GetProperty(index, kpidAttrib, &prop));
		if (prop.vt == VT_EMPTY)
		{
			_processedFileInfo.Attrib = 0;
			_processedFileInfo.AttribDefined = false;
		}
		else
		{
			if (prop.vt != VT_UI4)
				return E_FAIL;
			_processedFileInfo.Attrib = prop.ulVal;
			_processedFileInfo.AttribDefined = true;
		}
	}

	RINOK(IsArchiveItemFolder(_archiveHandler, index, _processedFileInfo.isDir));

	{
		// Get Modified Time
		NWindows::NCOM::CPropVariant prop;
		RINOK(_archiveHandler->GetProperty(index, kpidMTime, &prop));
		_processedFileInfo.MTimeDefined = false;
		switch (prop.vt)
		{
		case VT_EMPTY:
			// _processedFileInfo.MTime = _utcMTimeDefault;
			break;
		case VT_FILETIME:
			_processedFileInfo.MTime = prop.filetime;
			_processedFileInfo.MTimeDefined = true;
			break;
		default:
			return E_FAIL;
		}

	}
	{
		// Get Size
		NWindows::NCOM::CPropVariant prop;
		RINOK(_archiveHandler->GetProperty(index, kpidSize, &prop));
		UInt64 newFileSize;
		/* bool newFileSizeDefined = */ ConvertPropVariantToUInt64(prop, newFileSize);
	}


	{
		// Create folders for file
		int slashPos = _filePath.ReverseFind_PathSepar();
		if (slashPos >= 0)
			CreateComplexDir(_directoryPath + us2fs(_filePath.Left(slashPos)));
	}

	FString fullProcessedPath = _directoryPath + us2fs(_filePath);
	_diskFilePath = fullProcessedPath;

	if (_processedFileInfo.isDir)
	{
		CreateComplexDir(fullProcessedPath);
	}
	else
	{
		NFind::CFileInfo fi;
		if (fi.Find(fullProcessedPath))
		{
			if (!DeleteFileAlways(fullProcessedPath))
			{
				//PrintError("Can not delete output file", fullProcessedPath);
				return E_ABORT;
			}
		}

		_outFileStreamSpec = new COutFileStream;
		CMyComPtr<ISequentialOutStream> outStreamLoc(_outFileStreamSpec);
		if (!_outFileStreamSpec->Open(fullProcessedPath, CREATE_ALWAYS))
		{
			//PrintError("Can not open output file", fullProcessedPath);
			return E_ABORT;
		}
		_outFileStream = outStreamLoc;
		*outStream = outStreamLoc.Detach();
	}
	return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::PrepareOperation(Int32 askExtractMode)
{
	_extractMode = false;
	switch (askExtractMode)
	{
	case NArchive::NExtract::NAskMode::kExtract:  _extractMode = true; break;
	};
	switch (askExtractMode)
	{
	case NArchive::NExtract::NAskMode::kExtract:  Print(kExtractingString); break;
	case NArchive::NExtract::NAskMode::kTest:  Print(kTestingString); break;
	case NArchive::NExtract::NAskMode::kSkip:  Print(kSkippingString); break;
	};
	Print(_filePath);
	return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::SetOperationResult(Int32 operationResult)
{
	switch (operationResult)
	{
	case NArchive::NExtract::NOperationResult::kOK:
		break;
	default:
	{
		NumErrors++;
		Print("  :  ");
		const char *s = NULL;
		switch (operationResult)
		{
		case NArchive::NExtract::NOperationResult::kUnsupportedMethod:
			s = kUnsupportedMethod;
			break;
		case NArchive::NExtract::NOperationResult::kCRCError:
			s = kCRCFailed;
			break;
		case NArchive::NExtract::NOperationResult::kDataError:
			s = kDataError;
			break;
		case NArchive::NExtract::NOperationResult::kUnavailable:
			s = kUnavailableData;
			break;
		case NArchive::NExtract::NOperationResult::kUnexpectedEnd:
			s = kUnexpectedEnd;
			break;
		case NArchive::NExtract::NOperationResult::kDataAfterEnd:
			s = kDataAfterEnd;
			break;
		case NArchive::NExtract::NOperationResult::kIsNotArc:
			s = kIsNotArc;
			break;
		case NArchive::NExtract::NOperationResult::kHeadersError:
			s = kHeadersError;
			break;
		}
		if (s)
		{
			Print("Error : ");
			Print(s);
		}
		else
		{
			char temp[16];
			ConvertUInt32ToString(operationResult, temp);
			Print("Error #");
			Print(temp);
		}
	}
	}

	if (_outFileStream)
	{
		if (_processedFileInfo.MTimeDefined)
			_outFileStreamSpec->SetMTime(&_processedFileInfo.MTime);
		RINOK(_outFileStreamSpec->Close());
	}
	_outFileStream.Release();
	if (_extractMode && _processedFileInfo.AttribDefined)
		SetFileAttrib_PosixHighDetect(_diskFilePath, _processedFileInfo.Attrib);
	PrintNewLine();
	return S_OK;
}


STDMETHODIMP CArchiveExtractCallback::CryptoGetTextPassword(BSTR *password)
{
	if (!PasswordIsDefined)
	{
		// You can ask real password here from user
		// Password = GetPassword(OutStream);
		// PasswordIsDefined = true;
		//PrintError("Password is not defined");
		return E_ABORT;
	}
	return StringToBstr(Password, password);
}
#define CLSID_Format CLSID_CFormat7z


struct test : public IUnknown, public CMyUnknownImp
{
public:
	MY_ADDREF_RELEASE
};

int main()
{
	HMODULE h = LoadLibrary(L"d:/7z/Debug/7z.dll");
	Func_CreateObject createObjectFunc = (Func_CreateObject)GetProcAddress(h, "CreateObject");
	CMyComPtr<IInArchive> archive;
	if (createObjectFunc(&CLSID_Format, &IID_IInArchive, (void **)&archive) != S_OK)
	{
		//PrintError("Can not get class object");
		return 1;
	}
	
	CInFileStream *fileSpec = new CInFileStream;
	CMyComPtr<IInStream> file = fileSpec;
	FString archiveName = L"d:/1.7z";
	if (!fileSpec->Open(archiveName))
	{
		//PrintError("Can not open archive file", archiveName);
		return 1;
	}

	CArchiveOpenCallback *openCallbackSpec = new CArchiveOpenCallback;
	CMyComPtr<IArchiveOpenCallback> openCallback(openCallbackSpec);
	openCallbackSpec->PasswordIsDefined = false;
	// openCallbackSpec->PasswordIsDefined = true;
	// openCallbackSpec->Password = L"1";

	const UInt64 scanSize = 1 << 23;
	if (archive->Open(file, &scanSize, openCallback) != S_OK)
	{
		//PrintError("Can not open file as archive", archiveName);
		return 1;
	}
	CArchiveExtractCallback *extractCallbackSpec = new CArchiveExtractCallback;
	CMyComPtr<IArchiveExtractCallback> extractCallback(extractCallbackSpec);
	extractCallbackSpec->Init(archive, FString("d:")); // second parameter is output folder path
	extractCallbackSpec->PasswordIsDefined = false;

	HRESULT result = archive->Extract(NULL, (UInt32)(Int32)(-1), false, extractCallback);

	if (result != S_OK)
	{
		//PrintError("Extract Error");
		return 1;
	}
    return 0;
}

