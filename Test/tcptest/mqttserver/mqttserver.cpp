#include "mqttserver.h"
#include "mongoose.h"
#include "simplethread.h"
#include <vector>
#include <set>

#define MGR_TIMEOUT_MS 300

mqttserver::mqttserver(QWidget *parent)
	: QWidget(parent)
	, mThread(NULL)
	, mExit(false)
{
	ui.setupUi(this);
	connect(ui.pushButtonStart, SIGNAL(clicked()), SLOT(onStart()));
	connect(ui.pushButtonStop, SIGNAL(clicked()), SLOT(onStop()));
}

mqttserver::~mqttserver()
{

}

void mqttserver::onStop()
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

void * mqttserver::threadProc(void * arg)
{
	mqttserver *This = reinterpret_cast<mqttserver*>(arg);
	This->innerThreadProc();
	return NULL;
}

static size_t mg_mqtt_next_topic(struct mg_mqtt_message *msg,
	struct mg_str *topic, uint8_t *qos,
	size_t pos) {
	unsigned char *buf = (unsigned char *)msg->dgram.ptr + pos;
	size_t new_pos;
	if (pos >= msg->dgram.len) return 0;

	topic->len = (size_t)(((unsigned)buf[0]) << 8 | buf[1]);
	topic->ptr = (char *)buf + 2;
	new_pos = pos + 2 + topic->len + (qos == NULL ? 0 : 1);
	if ((size_t)new_pos > msg->dgram.len) return 0;
	if (qos != NULL) *qos = buf[2 + topic->len];
	return new_pos;
}

size_t mg_mqtt_next_sub(struct mg_mqtt_message *msg, struct mg_str *topic,
	uint8_t *qos, size_t pos) {
	uint8_t tmp;
	return mg_mqtt_next_topic(msg, topic, qos == NULL ? &tmp : qos, pos);
}

size_t mg_mqtt_next_unsub(struct mg_mqtt_message *msg, struct mg_str *topic,
	size_t pos) {
	return mg_mqtt_next_topic(msg, topic, NULL, pos);
}

struct MqttClientNode {
	struct mg_connection *c;
	std::vector<std::string> topics;
};

struct MgrData
{
	std::string userName;
	std::string password;
	std::vector<MqttClientNode> nodes;
};

struct MqttClientNodeFind {
	MqttClientNodeFind(struct mg_connection *_c):c(_c) {

	}
	bool operator()(const MqttClientNode &node)const {
		return node.c == c;
	}

	struct mg_connection *c;
};

#define MQTT_CLEAN_SESSION 0x02
#define MQTT_HAS_WILL 0x04
#define MQTT_WILL_RETAIN 0x20
#define MQTT_HAS_PASSWORD 0x40
#define MQTT_HAS_USER_NAME 0x80

#define SKIP_PROP(ptr, ptrEnd) \
do{ \
	if (ptr + sizeof(uint16_t) > ptrEnd) throw -1; \
	uint16_t len; \
	memcpy(&len, ptr, sizeof(uint16_t)); \
	ptr += sizeof(uint16_t); \
	len = mg_ntohs(len); \
	if (ptr + len > ptrEnd)throw -1; \
	ptr += len; \
} while (false);

#define GET_PROP(ptr, ptrEnd, str) \
do{ \
	if (ptr + sizeof(uint16_t) > ptrEnd) throw -1; \
	uint16_t len; \
	memcpy(&len, ptr, sizeof(uint16_t)); \
	ptr += sizeof(uint16_t); \
	len = mg_ntohs(len); \
	if (ptr + len > ptrEnd)throw -1; \
	str.assign(ptr, len); \
	ptr += len; \
} while (false);



static bool getUserNameAndPassword(struct mg_mqtt_message *mm, std::string &userName, std::string &password) {
	bool success = false;
	const char *ptr = &mm->dgram.ptr[9];
	const char *const ptrEnd = mm->dgram.ptr + mm->dgram.len;
	uint8_t flag = *ptr;
	ptr += 3;//skip flag and keep alive
	//ptr += mm->props_size;

	try {
		SKIP_PROP(ptr, ptrEnd);		//skip client id
		//if (flag & MQTT_HAS_WILL) {
		//	SKIP_PROP(ptr, ptrEnd);		//skip topic
		//	SKIP_PROP(ptr, ptrEnd);		//skip message
		//}
		if (flag & MQTT_HAS_USER_NAME) {
			GET_PROP(ptr, ptrEnd, userName);
		}
		if (flag & MQTT_HAS_PASSWORD) {
			GET_PROP(ptr, ptrEnd, password);
		}
		success = true;
	}
	catch (...) {

	}
	return success;
}

static void fn_cmd(struct mg_connection *c, struct mg_mqtt_message *mm, MgrData &data) {
	std::vector<MqttClientNode>& nodes = data.nodes;
	switch (mm->cmd) {
	case MQTT_CMD_CONNECT: {
		if (mm->dgram.len < 9) {
			assert(false);
		}
		else if (mm->dgram.ptr[8] != 4) {
			assert(false);
		}
		else {
			std::string userName, password;
			getUserNameAndPassword(mm, userName, password);
			if (!data.userName.empty() && data.userName != userName) {
				return;
			}
			if (!data.password.empty() && data.password != password) {
				return;
			}
			uint8_t response[] = { 0,0 };
			mg_mqtt_send_header(c, MQTT_CMD_CONNACK, 0, sizeof(response));
			mg_send(c, response, sizeof(response));
		}
		break;
	}
	case MQTT_CMD_SUBSCRIBE: {
		std::vector<MqttClientNode>::iterator iter = std::find_if(nodes.begin(), nodes.end(), MqttClientNodeFind(c));
		if (iter == nodes.end()) {
			assert(false);
			break;
		}
		MqttClientNode&node = *iter;
		size_t pos = 4;		// Initial topic offset, where ID ends
		uint8_t qos;
		std::vector<uint8_t> resp;
		struct mg_str topic;
		while ((pos = mg_mqtt_next_sub(mm, &topic, &qos, pos)) > 0) {
			std::string tmp(topic.ptr, topic.len);
			//将+替换为*，使得mg_match生效
			for (std::string::iterator iterTxt = tmp.begin(); iterTxt != tmp.end(); ++iterTxt) {
				if (*iterTxt == '+') {
					*iterTxt = '*';
				}
			}
			node.topics.push_back(tmp);
			resp.push_back(qos);
		}
		mg_mqtt_send_header(c, MQTT_CMD_SUBACK, 0, resp.size() + 2);
		uint16_t id = mg_htons(mm->id);
		mg_send(c, &id, 2);
		mg_send(c, resp.data(), resp.size());
		break;
	}
	case MQTT_CMD_PUBLISH: {
		for (std::vector<MqttClientNode>::iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
			MqttClientNode& node = *iter;
			for (std::vector<std::string>::const_iterator iterTopic = node.topics.begin();
				iterTopic != node.topics.end(); ++iterTopic) {
				mg_str subTopic = mg_str(iterTopic->c_str());
				if (!mg_match(mm->topic, subTopic, NULL)) {
					continue;
				}
				mg_mqtt_opts pubOpts;
				memset(&pubOpts, 0, sizeof(pubOpts));
				pubOpts.topic = mm->topic;
				pubOpts.message = mm->data;
				pubOpts.qos = mm->qos;
				pubOpts.retain = false;
				mg_mqtt_pub(node.c, &pubOpts);
			}
		}
		break;
	}
	case MQTT_CMD_PINGREQ: {
		mg_mqtt_send_header(c, MQTT_CMD_PINGRESP, 0, 0);
		break;
	}
	}
}

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	struct MgrData *data = reinterpret_cast<struct MgrData*>(fn_data);
	std::vector<MqttClientNode>& nodes = data->nodes;
	switch (ev) {
	case MG_EV_ACCEPT: {
		MqttClientNode node;
		node.c = c;
		nodes.push_back(node);
		break;
	}
	case MG_EV_CLOSE: {
		std::vector<MqttClientNode>::iterator iter = std::find_if(nodes.begin(), nodes.end(), MqttClientNodeFind(c));
		if (iter != nodes.end()) {
			nodes.erase(iter);
		}
		else {
			assert(false);
		}
		break;
	}
	case MG_EV_MQTT_CMD: {
		struct mg_mqtt_message *mm = (struct mg_mqtt_message *) ev_data;
		fn_cmd(c, mm, *data);
		break;
	}
	default:
		break;
	}
}

void mqttserver::innerThreadProc()
{
	std::string listenPort;
	{
		SimpleMutexLocker locker(mMutex);
		listenPort = mListenPort.toStdString();
	}
	struct MgrData data;
	struct mg_mgr mgr;
	
	mg_mgr_init(&mgr);
	mg_mqtt_listen(&mgr, listenPort.c_str(), &fn, &data);

	for (;;) {
		mg_mgr_poll(&mgr, MGR_TIMEOUT_MS);
		SimpleMutexLocker locker(mMutex);
		if (mExit) {
			break;
		}
	}
	mg_mgr_free(&mgr);
}

void mqttserver::onStart()
{
	onStop();
	mListenPort = ui.lineEdit->text();
	mExit = false;
	mThread = new SimpleThread(&mqttserver::threadProc, this);
}
