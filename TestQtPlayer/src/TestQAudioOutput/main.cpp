#include <QtCore/QCoreApplication>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QThread>
//准备PCM数据
//ffmpeg -i Wildlife.wmv -f s16le out.pcm
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	QAudioFormat fmt;
	fmt.setSampleRate(44100 /** 2*/);
	fmt.setSampleSize(16);
	fmt.setChannelCount(2);
	fmt.setCodec("audio/pcm");
	fmt.setByteOrder(QAudioFormat::LittleEndian);
	fmt.setSampleType(QAudioFormat::UnSignedInt);

	QAudioOutput output(fmt);
	QIODevice *io = output.start();

	int size = output.periodSize();
	char *buf = new char[size];
	FILE *fp = fopen("out.pcm", "rb");
	while (!feof(fp))
	{
		if (output.bytesFree() < size)
		{
			QThread::msleep(10);
			continue;
		}
		int len = fread(buf, 1, size, fp);
		if (len <= 0)
		{
			break;
		}
		io->write(buf, len);
	}
	fclose(fp);

	return a.exec();
}
