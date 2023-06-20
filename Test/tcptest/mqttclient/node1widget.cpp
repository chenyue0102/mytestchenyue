#include "node1widget.h"
#include <vector>
#include "mongoose.h"

#define MGR_POLL_TIMEOUT_MS 300



Node1Widget::Node1Widget(QWidget *parent)
	: QWidget(parent)
	, mThread(NULL)
	, mExit(false)
{
	ui.setupUi(this);
	connect(ui.pushButtonConnect, SIGNAL(clicked()), SLOT(onConnect()));
	connect(ui.pushButtonDisconnect, SIGNAL(clicked()), SLOT(onDisconnect()));
	connect(ui.pushButtonPublish, SIGNAL(clicked()), SLOT(onPublic()));
	connect(this, SIGNAL(signalMsg(const QString &)), SLOT(onLog(const QString &)), Qt::QueuedConnection);
}

Node1Widget::~Node1Widget()
{
}

void Node1Widget::setServerAddress(const QString & address)
{
	SimpleMutexLocker locker(mMutex);
	mServerAddress = address;
}

void Node1Widget::setSub(const QString & sub)
{
	SimpleMutexLocker locker(mMutex);
	mSub = sub;
}

void Node1Widget::setPub(const QString & pub)
{
	SimpleMutexLocker locker(mMutex);
	mPub = pub;
}

void Node1Widget::publicMessage(const QString & topic, const QString & message)
{
	SimpleMutexLocker locker(mMutex);
	MQTTPublish pub;
	pub.topic = topic.toStdString();
	pub.message = message.toStdString();
	mPublics.push_back(pub);
}

void Node1Widget::onConnect()
{
	onDisconnect();
	mExit = false;
	mThread = new SimpleThread(&Node1Widget::threadProc, this);
}

void Node1Widget::onDisconnect()
{
	if (NULL != mThread) {
		{
			SimpleMutexLocker locker(mMutex);
			mExit = true;
		}
		mThread->join();
		delete mThread;
		mThread = NULL;
	}
}

void Node1Widget::onPublic()
{
	publicMessage(mPub, "public node:" + mSub);
}

void Node1Widget::onLog(const QString & log)
{
	ui.textBrowser->append(log);
}

void * Node1Widget::threadProc(void * arg)
{
	Node1Widget *w = reinterpret_cast<Node1Widget*>(arg);
	w->innerThreadProc();
	return NULL;
}

struct ClientData {
	Node1Widget *w;
	bool isError;
	std::string sub;

	ClientData():w(NULL),isError(false) {

	}
};

static void onMQTTMsg(struct mg_connection *c, struct mg_mqtt_message *mm, ClientData *data) {
	switch (mm->cmd) {
	case MQTT_CMD_PUBLISH: {
		std::string topic(mm->topic.ptr, mm->topic.len);
		std::string msg(mm->data.ptr, mm->data.len);
		QString str = QString("topic:") + QString::fromStdString(topic) + QString(" msg:") + QString::fromStdString(msg);
		emit data->w->signalMsg(str);
		break;
	}
	}
}

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	ClientData *data = reinterpret_cast<ClientData*>(fn_data);
	switch (ev) {
	case MG_EV_ERROR: {
		data->isError = true;
		emit data->w->signalMsg("error");
		break;
	}case MG_EV_CONNECT: {
		emit data->w->signalMsg("connect");
		break;
	}case MG_EV_MQTT_OPEN: {
		struct mg_str subTopic = mg_str(data->sub.c_str());
		struct mg_mqtt_opts subOpts;
		memset(&subOpts, 0, sizeof(subOpts));
		subOpts.topic = subTopic;
		subOpts.qos = 1;
		mg_mqtt_sub(c, &subOpts);
		break;
	}case MG_EV_MQTT_MSG: {
		struct mg_mqtt_message *mm = (struct mg_mqtt_message *) ev_data;
		onMQTTMsg(c, mm, data);
		break;
	}case MG_EV_CLOSE: {
		emit data->w->signalMsg("close");
		break;
	}
	default:
		break;
	}
}

void Node1Widget::innerThreadProc()
{
	ClientData data;
	data.w = this;

	std::string address;
	{
		SimpleMutexLocker locker(mMutex);
		address = mServerAddress.toStdString();
		data.sub = mSub.toStdString();
	}
	mg_connection *c = NULL;
	mg_mgr mgr;
	mg_mgr_init(&mgr);
	struct mg_mqtt_opts opts;
	memset(&opts, 0, sizeof(opts));
	opts.clean = true;
	opts.qos = 1;
	opts.topic = mg_str("mg/clnt/test");
	opts.version = 4;
	opts.message = mg_str("bye");
	opts.user = mg_str("user");
	opts.pass = mg_str("password");

	c = mg_mqtt_connect(&mgr, address.c_str(), &opts, fn, &data);
	if (NULL == c) {
		mg_mgr_init(&mgr);
		assert(false);
		return;
	}
	for (;;) {
		mg_mgr_poll(&mgr, MGR_POLL_TIMEOUT_MS);
		if (data.isError) {
			break;
		}
		std::vector< MQTTPublish> pubs;
		{
			SimpleMutexLocker locker(mMutex);
			if (mExit) {
				break;
			}
			pubs.swap(mPublics);
		}
		std::vector< MQTTPublish>::const_iterator iter = pubs.begin();
		for (; iter != pubs.end(); ++iter) {
			mg_mqtt_opts pubOpts;
			memset(&pubOpts, 0, sizeof(pubOpts));
			pubOpts.topic = mg_str(iter->topic.c_str());
			pubOpts.message = mg_str(iter->message.c_str());
			pubOpts.qos = 1;
			pubOpts.retain = false;
			mg_mqtt_pub(c, &pubOpts);
		}
	}
	mg_mgr_free(&mgr);
}
