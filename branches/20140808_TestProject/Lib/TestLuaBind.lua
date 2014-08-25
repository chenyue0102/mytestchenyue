require "Serialize"

function LuaInit()
	_G.m_WindowArray={}
    _G._class = {}
	DuiLib.CPaintManagerUI.SetResourcePath("D:\\SnsCode\\Test\\chenyue\\Lib\\Skin")
end

CLuaSnsIndex = {wSnsCID = 0, wSnsTID = 0, dwPID = 0}
function CLuaSnsIndex:new(o)
    o = o or {}
    setmetatable(o,self)
    self.__index = self
    return o
end

function CLuaSnsIndex:__tostring()
    return "wSnsCID="..self.wSnsCID.."wSnsTID="..self.wSnsTID.."dwPID="..self.dwPID.."\n"
end

function CLuaSnsIndex:Read(seri)
    self.wSnsCID = seri:ReadWORD()
    if nil==self.wSnsCID then
        return false
    end
    self.wSnsTID = seri:ReadWORD()
    if nil==self.wSnsTID then
        return false
    end
    self.dwPID = seri:ReadDWORD()
    if nil==self.dwPID then
        return false
    end
    return true
end

CLuaTimeStamp = {stSnsClientSnsIndex=CLuaSnsIndex:new(), dwTimeStamp = 0}
function CLuaTimeStamp:new(o)
    o = o or {}
    setmetatable(o,self)
    self.__index = self
    return o
end
function CLuaTimeStamp:Read(seri)
    if not self.stSnsClientSnsIndex:Read(seri) then
        return false
    end
    self.dwTimeStamp = seri:ReadDWORD()
    if not self.dwTimeStamp then
        return false
    end
    return true
end

function CLuaTimeStamp:__tostring()
    return tostring(self.stSnsClientSnsIndex).."dwTimeStamp="..self.dwTimeStamp.."\n"
end

function LuaTestSerialize(buffer)
    local seri = Serialize.CSerializeHelper:new()
    seri:SetBuffer(buffer)
    local snsindex = CLuaTimeStamp:new()
    snsindex:Read(seri)
    local str = tostring(snsindex)
    print(str)
end

CLuaDefineClass = {__gc=function(self) self:__finalize() end}

function CLuaDefineClass:new(o)
    o = o or {}
    setmetatable(o,self)
    self.__index = self

    o:__init()
    return o
end

function CLuaDefineClass:__init()
    self.m_strName = "Jackson"
end

function CLuaDefineClass:__finalize()
    print("__finalize CLuaDefineClass")
end

function CLuaDefineClass:Output(tb)
    local strself = type(self)
    print(self.m_strName)
    tb[100]=self.m_strName
end

function LuaTestDefineClass()
    local t = CLuaDefineClass:new()
    local s = CLuaDefineClass:new()
    
    s.m_strName = "Bush"
    local str={}
    t:Output(str)
    s:Output(str)
    print(str[100])
end

function LuaMain()
	--for i=1,500,1 do
	LuaInitWindow()
	--end
end

function LuaFindAndBringWindowToTop(dwtype, comparevalue)
	local wintable=_G.m_WindowArray
	for key, value in pairsByKeys(wintable) do  
		local compreresult=value:Compare(dwtype,comparevalue)
		if (compreresult) then
			value:BringWindowToTop()
			break
		end
	end
end

function LuaDealMessage(msgid, strbuffer)
	local wintable=_G.m_WindowArray
	for key, value in pairsByKeys(wintable) do  
		value:OnDealMessage(msgid,strbuffer)
	end
end

function pairsByKeys(t)  
    local a = {}  
    for n in pairs(t) do  
        a[#a+1] = n  
    end  
    table.sort(a)  
    local i = 0  
    return function()  
        i = i + 1  
        return a[i], t[a[i]]  
    end  
end

function LuaTestTable()
	local testtable={};
	table.insert(testtable, "first")
	table.insert(testtable, "second")
	table.insert(testtable, "third")
	table.insert(testtable, "fourth")
	table.remove(testtable,1)
	for key, value in pairsByKeys(testtable) do  
		print(key,value)
		if 2==key then
			break
		end
	end
end

function LuaEraseWindow(win)
	local wintable=_G.m_WindowArray
	for key, value in pairsByKeys(wintable) do  
		--print(type(value), class_info(value).name)
		--print(type(win), class_info(win).name)
		local hwndvalue=value:GetHWND()
		local hwndwin=win:GetHWND()
		if hwndvalue==hwndwin then
			--print("remove")
			table.remove(wintable,key)
			break
		end
	end
	
	LuaCollectGarbage()
end

function LuaInsertWindow(win)
	local wintable=_G.m_WindowArray
	table.insert(wintable, win)
end

function LuaTestCopyClass()
	local onenode=CTestNode()
	local copynode=CTestNode(onenode)
	onenode:SetIndex(99)
	copynode:SetIndex(99)
	
	local onetlv=TKSnsClientTLV()
	onetlv:SetString(99,"abc"..99)
	local copytlv=TKSnsClientTLV(onetlv)
	print("copytlv",copytlv:ToString())
end

function LuaTestMap()
	local testmap=DWORDSTRINGMap()
	for i=1,100,1 do
		local testpair=DWORDSTRINGMapPair(i,"testmap"..i)
		testmap:Insert(testpair)
		testpair=nil
	end
	for i=1,100,2 do
		testmap:EraseKey(i)
	end
	
	local itor=testmap:Find(100)
	if itor ~= testmap:End()
	then
		testmap:Erase(itor)
	end
	
	itor=testmap:Begin()
	while itor~=testmap:End() do
		local onevalue = itor:GetValue()
		print(onevalue.First,onevalue.Second,type(onevalue), class_info(onevalue).name)
		itor:Increment()
	end
end

function LuaTestNetworkDeal(msgid, strBuffer)
	--if 1== msgid
	--then
	--for i=1,500,1 do
		local stSnsClientGetSnsTimeStampListFromServer = TKSnsClientGetSnsTimeStampListFromServer()
		local seri=CSerialization(strBuffer)
		seri:SetSerializationType(1)
		stSnsClientGetSnsTimeStampListFromServer:Serialization(seri)
		local itor = stSnsClientGetSnsTimeStampListFromServer.SnsClientSnsTimeStampArray:Begin()
		while itor~=stSnsClientGetSnsTimeStampListFromServer.SnsClientSnsTimeStampArray:End() do
			local onevalue=itor:GetValue()
			print(type(onevalue), class_info(onevalue).name, "CID=",onevalue.stSnsClientSnsIndex.wSnsCID,
			"TID=",onevalue.stSnsClientSnsIndex.wSnsTID, "PID=",onevalue.stSnsClientSnsIndex.dwPID, "dwTimeStamp", onevalue.dwTimeStamp)
			onevalue=nil
			itor:Increment()
		end
	--end
	--end
end

function LuaTestTlvToString()
	local tlv=TKSnsClientTLV()
	local i=99
	tlv:SetString(i,"abc"..i)
	print(tlv:ToString())
	tlv:SetDword(i,i)
	print(tlv:ToDword())
end

function LuaTestSTL()
	local stl=TKSnsClientTLVVector()
	print(type(stl), class_info(stl).name)
	local tlv=TKSnsClientTLV()
	for i=1,100,1 do
		tlv:SetDword(i,i)
		stl:PushBack(tlv)
	end
	for i=1,100,1 do
		tlv:SetString(i,"abc"..i)
		stl:PushBack(tlv)
	end
	print("size",stl:Size())

	
	local itor=stl:Begin()
	print(type(itor), class_info(itor).name)
	while itor ~= stl:End() do
		local onevalue=itor:GetValue()
		if 4==onevalue.dwType
		then
			print("onevalue",type(onevalue), class_info(onevalue).name,onevalue:ToDword())
		else
			print("onevalue",type(onevalue), class_info(onevalue).name,onevalue:ToString())
		end
		onevalue=nil
		itor=stl:Erase(itor)
	end
	print("size",stl:Size())
end

function LuaTestString()
	local s=GetString()
	print(s,string.len(s))
end

function LuaTestSerialization()
	local tlv=TKSnsClientTLV()
	tlv:SetString(123,"abc123456")
	local cs=CSerialization()
	cs:SetSerializationType(2)
	tlv:Serialization(cs)
	
	local str= std.string()
	cs:ToBuffer(str)
	print(type(str), class_info(str).name)
	local tlv2=TKSnsClientTLV()
	local cs2=CSerialization(str)
	cs2:SetSerializationType(1)
	tlv2:Serialization(cs2)
end

function LuaTestManager()
	local NodeManager = CTestNodeManager()
	NodeManager:InitNode(2)

	local OneNode = NodeManager:GetNode(1);
	local bIsExist = NodeManager:IsNodeExist(OneNode)
	print("bIsExist",bIsExist)

	local NodeRef=NodeManager:GetRefNode(0);
	local tempnode=OneNode
	local NodeIndex=OneNode:GetIndex()
	local newNode=CTestNode()
	print("NodeIndex",NodeIndex)

	globalNode=OneNode

	
	NodeManager=nil
	globalNode=nil
	OneNode=nil
	NodeRef=nil
	tempnode=nil
	newNode=nil
	NodeIndex=nil
	
	LuaCollectGarbage()
	LuaCollectGarbage()
	LuaCollectGarbage()

	--print("global", globalNode:GetIndex())
end

function LuaCollectGarbage()
	print("Before LuaCollectGarbage")
	collectgarbage("collect")
	print("After LuaCollectGarbage")
end

function LuaTestStaticFun()
	local s=CTestNode()
	local l=CTestNode.GetCount()
	print("LuaTestStaticFun",l)
end

function LuaTestGetValue()
	local NodeManager = CTestNodeManager()
	NodeManager:InitNode(2)
	local MyNode=CTestNode()
	NodeManager:GetNodeValue(0,MyNode)
	NodeManager:GetRefNodeValue(1,MyNode)

end

function LuaTestContainer()
	local l = CChildContainer()
	l:InitManager()
	l:TestCacheNode()
	--print("class_info",class_info(l.CacheNode0).name);
	l.CacheNode0=nil
	l.CacheNode1=nil
	l=nil
	LuaCollectGarbage()
	LuaCollectGarbage()
	LuaCollectGarbage()
	LuaCollectGarbage()
	LuaCollectGarbage()
end

class 'CChildContainer'(CTestContainer)
function CChildContainer:__init()
	CTestContainer.__init(self)
end

function CChildContainer:InitManager()
	local manager = self:GetNodeManager()
	manager:InitNode(2)
	self.CacheNode0 = manager:GetNode(0)
	self.CacheNode1=manager:GetNode(1)
end

function CChildContainer:TestCacheNode()
	print("TestCacheNode",self.CacheNode0:GetIndex())
	print("TestCacheNode",self.CacheNode1:GetIndex())
end

class 'CInviteSnsMember'(DuiLib.CFrameWindow)
function CInviteSnsMember:__init()
	DuiLib.CFrameWindow.__init(self)
	self.m_FrameBackImageType=2
	
	self:SetInnerSkinFile("TKSnsUICreateSns\\InviteSnsMember\\AddGroupMemberPage.xml")
	self.m_dwType=2
end

function CInviteSnsMember:Init()
	DuiLib.CFrameWindow.Init(self)
	LuaInsertWindow(self)
	local pmanager=self:GetManager()
	--print(type(pmanager), class_info(pmanager).name)
	local proot=pmanager:GetRoot()
	--print(type(proot), class_info(proot).name)
	local pcontrol=LuaFindSubControlByName(pmanager,proot,"CombContacts")
	self.m_pCombContacts=pcontrol
	self.m_pEditSearch=LuaFindSubControlByName(pmanager,proot,"EditSearch")
	--print(type(pcontrol), class_info(pcontrol).name)
	local pcontainer=Conver.ToCContainerUI(pcontrol)
	local pcombobox=Conver.ToCComboUI(pcontrol)
	--print(type(pcontainer), class_info(pcontainer).name)
	for i=1,10,1 do
		local itemui=CreateUI.CreateCListLabelElementUI(pcontainer, -1);
		--print(type(itemui), class_info(itemui).name)
		itemui:SetText("item"..i)
	end
	pcombobox:SelectItem(0,true)
	
	local listitemxml="TKSnsUICreateSns\\CreateGroup\\PvtContactItem.xml"
	local plistitemcontrol=LuaFindSubControlByName(pmanager,proot,"ListContacts")
	local plistcontainer=Conver.ToCContainerUI(plistitemcontrol)
	
	for i=1,10,1 do
		local poneitemroot=BuilderCControlUI(listitemxml,nil,self, pmanager,plistitemcontrol)
		local poneitemlabelcontrol=LuaFindSubControlByName(pmanager,poneitemroot,"LabelName")
		poneitemlabelcontrol:SetText("张大宝"..i)
	end	
end

function CInviteSnsMember:Notify(msg)
	DuiLib.CFrameWindow.Notify(self,msg)
	--LuaPrintClassInfo(msg.sType)
	if msg.sType=="itemselect" then
		--LuaPrintClassInfo(self.m_pCombContacts)
		--LuaPrintClassInfo(msg.pSender)
		--if 0 ~= CompareControl(self.m_pCombContacts,msg.pSender) then
		if self.m_pCombContacts==msg.pSender then
			self.m_pEditSearch:SetText(msg.pSender:GetText())
		end
	end
end

function CInviteSnsMember:OnFinalMessage(hwnd)
	self.m_pCombContacts=nil
	self.m_pEditSearch=nil
	LuaEraseWindow(self)
	DuiLib.CFrameWindow.OnFinalMessage(self, hwnd)
end

function CInviteSnsMember:Compare(dwtype,snsindex)
	if self.m_dwType==dwtype then
		if LuaIsEqualClass(self.m_stSnsIndex,snsindex) then
			if self.m_stSnsIndex.dwPID==snsindex.dwPID then
				return true
			end
		end
	end
	return false
	--LuaPrintClassInfo(self.m_stSnsIndex)
	--LuaPrintClassInfo(snsindex)
end

function LuaCreateInviteDialog(stSnsIndex)
	local strTest="选择联系人"
	local NewWindow = CInviteSnsMember()
	local style=0x10000000+0x10ce0000
	--print(type(strXml))
	--print(class_info(strXml).name);
	
	NewWindow.m_stSnsIndex = TKSnsClientSnsIndex(stSnsIndex)
	--print(LuaIsEqualClass(NewWindow.m_stSnsIndex,stSnsIndex),LuaIsEqualClass(NewWindow,stSnsIndex))
	NewWindow:Create(nil,strTest,style,0,0,0,580,440,nil)
	NewWindow:ShowWindow(true,true)
	NewWindow:CenterWindow()
	--NewWindow:PostMessage(16,0,0)
	NewWindow=nil
end

class 'CAboutDlg' (DuiLib.CFrameWindow)
function CAboutDlg:__init()
	DuiLib.CFrameWindow.__init(self)
	self.m_FrameBackImageType=1
	
	self:SetInnerSkinFile("TKSnsUIMainPanel\\AboutDlg\\AboutDlg.xml")
	self.m_dwType=1
end

function CAboutDlg:Init()
	--self.m_FrameBackImageType=1
	DuiLib.CFrameWindow.Init(self)
	LuaInsertWindow(self)
end

function CAboutDlg:OnFinalMessage(hwnd)
	LuaEraseWindow(self)
	DuiLib.CFrameWindow.OnFinalMessage(self, hwnd)
end

function CAboutDlg:Notify(msg)
	DuiLib.CFrameWindow.Notify(self,msg)
	if msg.sType == "link"	then
		local pControl=msg.pSender
		--print(type(pControl), class_info(pControl).name)
		local strName=pControl:GetName()
		--print(type(strName), class_info(strName).name)
		if strName=="TextLinkOfficial"
		then
			print("open url")
		end
	elseif msg.sType=="windowinit" then
		local pmanager = self:GetManager()
		--print(type(pmanager), class_info(pmanager).name)
		local proot=pmanager:GetRoot()
		--print(type(proot), class_info(proot).name)
		local pcontrol = pmanager:FindSubControlByName(proot,"CtrlVersion")
		--print(type(pcontrol), class_info(pcontrol).name)
		pcontrol:SetText("Lua设置版本号")
	end
end

function CAboutDlg:Compare(dwtype,value)
	if self.m_dwType==dwtype then
		return true
	end
	return false
end

function CAboutDlg:OnDealMessage(msgid,strbuffer)
	DuiLib.CFrameWindow.OnDealMessage(self,msgid,strbuffer)
	if 1==msgid then
		LuaSetTheme(self,strbuffer)
	end
end

function LuaCreateWindow()
	local strTest="king of fighter 97"
	local NewWindow = CAboutDlg()
	local style=0x10000000+0x10ce0000
	--print(type(strXml))
	--print(class_info(strXml).name);
	NewWindow:Create(nil,strTest,style,0,0,0,0,0,nil)
	NewWindow:ShowWindow(true,true)
	NewWindow:CenterWindow()
	--NewWindow:PostMessage(16,0,0)
    print(type(NewWindow))
	NewWindow=nil
end

function LuaInitWindow()
	--for i=1,5,1 do
		LuaCreateWindow()
	--end
	
	
	--DuiLib.CPaintManagerUI.MessageLoop()
	--LuaCollectGarbage()
	--LuaCollectGarbage()
	--LuaCollectGarbage()
end

function LuaFindSubControlByName(pmanager, proot, controlname)
	local findcontrol=nil
	if nil ~= pmanager then
		if nil ~= proot then
			if nil ~= controlname then
				findcontrol = pmanager:FindSubControlByName(proot,controlname)
			end
		end
	end
	return findcontrol
end

function LuaPrintClassInfo(obj)
	print(type(obj), class_info(obj).name)
end 

function LuaIsEqualClass(classleft,classright)
	--print(type(classleft),type(classright),class_info(classleft).name,class_info(classright).name)
	if type(classleft)==type(classright) then
		if class_info(classleft).name==class_info(classright).name then
			return true
		end
	end
	return false;
end

function LuaSetTheme(win,str)
	local theme=MSGSTRU_SNSUI_SETTING_THEME()
	theme:Serialization(str)
	win:SetTheme(theme)
end