// testgstreamer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include "gst/gst.h"
#include"gst/video/videooverlay.h"
typedef struct _CustomData {
	GstElement *pipeline;
	GstElement *source;
	GstElement *filter;
	GstElement *sink;
	GstElement *filter_audio;
	GstElement *sink_audio;
	GstElement *tee;
	GMainLoop *loop;
	gdouble rate = 1.0;
}CustomData;
static void pad_added_handler(GstElement *src, GstPad *pad, CustomData *data) {
	/*if (gst_pad_is_linked(sink_pad)) {
		gst_object_unref(sink_pad);
		return;
	}*/

	GstCaps  *new_pad_caps = gst_pad_get_current_caps(pad);
	GstStructure *new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
	const gchar* new_pad_type = gst_structure_get_name(new_pad_struct);
	GstPad *sink_pad = NULL;
	if (g_str_has_prefix(new_pad_type, "video/x-raw")) {
		sink_pad = gst_element_get_static_pad(data->filter, "video_sink");
	}
	else if (g_str_has_prefix(new_pad_type, "audio/x-raw")){
		sink_pad = gst_element_get_static_pad(data->tee, "sink");
	}
	else {
		assert(false);
	}
	GstPadLinkReturn ret = GST_PAD_LINK_WRONG_HIERARCHY;
	//gst_pad_get_current_caps(pad);
	if (GST_PAD_LINK_FAILED(ret = gst_pad_link(pad, sink_pad))) {
		g_print("link failed\n");
	}
	else {
		g_print("link success\n");
	}
	exit:
	if (NULL != new_pad_caps) {
		gst_caps_unref(new_pad_caps);
	}
	gst_object_unref(sink_pad);
}

gboolean handle_keyboard(GIOChannel *source, GIOCondition cond, CustomData *data) {
	gchar *str = NULL;
	if (g_io_channel_read_line(source, &str, NULL, NULL, NULL) != G_IO_STATUS_NORMAL) {
		return TRUE;
	}
	gint64 duration = 0;
	gst_element_query_position(data->source, GST_FORMAT_TIME, &duration);
	switch (str[0])
	{
	case 'p': {
		gst_element_set_state(data->pipeline, GST_STATE_PAUSED);
	}break;
	case 'r': {
		gst_element_set_state(data->pipeline, GST_STATE_PLAYING);
		GstEvent *event = gst_event_new_seek(1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, duration, GST_SEEK_TYPE_END, 0);
		gst_element_send_event(data->source, event);
	}break;
	case 's': {
		GstEvent *event = gst_event_new_seek(1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, 10 * GST_SECOND, GST_SEEK_TYPE_END, 0);
		gst_element_send_event(data->source, event);
	}break;
	case 'f': {
		data->rate *= 2;
		GstEvent *event = gst_event_new_seek(data->rate, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, duration, GST_SEEK_TYPE_END, 0);
		gst_element_send_event(data->source, event);
	}break;
	case 'g': {
		data->rate /= 2;
		GstEvent *event = gst_event_new_seek(data->rate, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, duration, GST_SEEK_TYPE_END, 0);
		gst_element_send_event(data->source, event);
	}break;
	case 't': {
		GstEvent *event = gst_event_new_step(GST_FORMAT_BUFFERS, 1, ABS(2.5), TRUE, FALSE);
		gst_element_send_event(data->sink, event);
	}break;
	case 'q':
		g_main_loop_quit(data->loop);
		break;
	default:
		break;
	}
	g_free(str);
}

int test() {
	GstElementFactory *source_factory = gst_element_factory_find("uridecodebin");
	GstElement *source = gst_element_factory_create(source_factory, "source");

	GstElement *filter = gst_element_factory_make("timeoverlay", "filter");
	GstElement *sink = gst_element_factory_make("autovideosink", "sink");

	GstElement *tee = gst_element_factory_make("tee", "tee");

	GstElement *queue_audio = gst_element_factory_make("queue", NULL);
	GstElement *filter_audio = gst_element_factory_make("audioconvert", "convert");
	GstElement *filter_resample = gst_element_factory_make("audioresample", "resample");
	GstElement *sink_audio = gst_element_factory_make("autoaudiosink", "sink_audio");

	GstElement *queue_audio_display = gst_element_factory_make("queue", NULL);
	GstElement *filter_audio2 = gst_element_factory_make("audioconvert", NULL);
	GstElement *wav_scope = gst_element_factory_make("wavescope", NULL);
	GstElement *videoconvert = gst_element_factory_make("videoconvert", NULL);
	GstElement *audio_display_sink = gst_element_factory_make("autovideosink", NULL);

	//source->timeoverlay->autovideosink
	//      ->tee->queue->audioconvert->audioresample->autoaudiosink
	//           ->queue->wavescope->videoconvert->autovideosink

	GstElement *pipeline = gst_pipeline_new("test-pipeline");
	g_print("test\n");

	gst_bin_add_many(GST_BIN(pipeline),
		source,
		filter, sink,
		tee,
		queue_audio, filter_audio, filter_resample, sink_audio,
		queue_audio_display, filter_audio2, wav_scope, videoconvert, audio_display_sink,
		NULL);
#if 0
	if (!gst_element_link_many(source, filter, sink, NULL)) {
		gst_object_unref(pipeline);
		return -1;
	}
	g_object_set(source, "pattern", 0, NULL);
#else
	if (!gst_element_link(filter, sink)) {
		gst_object_unref(pipeline);
		return -1;
	}
	if (!gst_element_link_many(queue_audio, filter_audio, filter_resample, sink_audio, NULL)) {
		gst_object_unref(pipeline);
		return -1;
	}
	if (!gst_element_link_many(queue_audio_display, filter_audio2, wav_scope, videoconvert, audio_display_sink, NULL)) {
		gst_object_unref(pipeline);
		return -1;
	}
	g_object_set(source, "uri", "file:///d:/v1080.mp4");
	CustomData data;
	data.pipeline = pipeline;
	data.source = source;
	data.filter = filter;
	data.sink = sink;
	data.filter_audio = filter_audio;
	data.sink_audio = sink_audio;
	data.tee = tee;
	g_signal_connect(source, "pad-added", G_CALLBACK(&pad_added_handler), &data);

	GstPad *tee_pad = gst_element_get_request_pad(tee, "src_%u");
	GstPad *queue_audio_pad = gst_element_get_static_pad(queue_audio, "sink");
	if (GST_PAD_LINK_OK != gst_pad_link(tee_pad, queue_audio_pad)) {
		assert(false);
		return -1;
	}
	GstPad *tee_pad2 = gst_element_get_request_pad(tee, "src_%u");
	GstPad *queue_audio_display_pad = gst_element_get_static_pad(queue_audio_display, "sink");
	if (GST_PAD_LINK_OK != gst_pad_link(tee_pad2, queue_audio_display_pad)) {
		assert(false);
		return -1;
	}
	gst_object_unref(queue_audio_pad);
	gst_object_unref(queue_audio_display_pad);
#endif


	GstStateChangeReturn ret = GST_STATE_CHANGE_FAILURE;
	if (GST_STATE_CHANGE_FAILURE == (ret = gst_element_set_state(pipeline, GST_STATE_PLAYING))) {
		gst_object_unref(pipeline);
		return -1;
	}

	GIOChannel *io_stdin = g_io_channel_win32_new_fd(_fileno(stdin));//g_io_channel_unix_new 
	g_io_add_watch(io_stdin, G_IO_IN, (GIOFunc)&handle_keyboard, &data);

	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	data.loop = loop;
	g_main_loop_run(loop);

	gst_element_release_request_pad(tee, tee_pad);
	gst_element_release_request_pad(tee, tee_pad2);
	gst_object_unref(tee_pad);
	gst_object_unref(tee_pad2);
#if 0
	gint64 duration = 0, start = 0, end = 0, current = 0;
	gboolean seek_enable = false, seek_done = false;
	GstBus *bus = gst_element_get_bus(pipeline);
	gboolean terminate = FALSE;
	do
	{
		GstMessage *msg = gst_bus_timed_pop_filtered(bus, /*GST_CLOCK_TIME_NONE*/100 * GST_MSECOND, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_DURATION_CHANGED));

		if (NULL != msg) {
			GError *err;
			gchar *debug_info;
			switch (GST_MESSAGE_TYPE(msg)) {
			case GST_MESSAGE_ERROR:
				gst_message_parse_error(msg, &err, &debug_info);
				terminate = TRUE;
				g_print("element:%s %s\n", GST_OBJECT_NAME(msg->src), err->message);
				g_clear_error(&err);
				g_free(debug_info);
				break;
			case GST_MESSAGE_EOS:
				terminate = TRUE;
				break;
			case GST_MESSAGE_STATE_CHANGED:
				if (GST_MESSAGE_SRC(msg) == GST_OBJECT(pipeline)) {
					GstState oldState, newState, pendingState;
					gst_message_parse_state_changed(msg, &oldState, &newState, &pendingState);
					const gchar *name1 = gst_element_state_get_name(oldState);
					const gchar *name2 = gst_element_state_get_name(newState);
					g_print("from:%s to:%s\n", name1, name2);
					if (newState == GST_STATE_PLAYING) {
						GstQuery *query = 0;
						query = gst_query_new_seeking(GST_FORMAT_TIME);
						if (gst_element_query(source, query)) {
							gst_query_parse_seeking(query, NULL, &seek_enable, &start, &end);
						}

						gst_query_unref(query);
					}
				}
				break;
			case GST_MESSAGE_DURATION_CHANGED:
				duration = GST_CLOCK_TIME_NONE;
				//gst_element_query_duration(pipeline, GST_FORMAT_TIME, &duration);
				break;
			default:
				break;
			}
			gst_message_unref(msg);
		}
		else {
			if (!gst_element_query_position(source, GST_FORMAT_TIME, &current)) {
				assert(false);
			}
			if (!GST_CLOCK_TIME_IS_VALID(duration)) {
				if (!gst_element_query_duration(source, GST_FORMAT_TIME, &duration)) {
					assert(false);
				}
			}
			if (seek_enable && !seek_done) {
				seek_done = true;
				gst_element_seek_simple(source, GST_FORMAT_TIME, (GstSeekFlags)(GST_SEEK_FLAG_FLUSH /*| GST_SEEK_FLAG_KEY_UNIT*/), 20 * GST_SECOND);
			}
		}
	} while (!terminate);
	gst_object_unref(bus);
#endif

	g_main_loop_unref(loop);
	g_io_channel_unref(io_stdin);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
	gst_object_unref(source_factory);
}

#include <gst/audio/audio.h>
typedef struct _CustomData2 {
	GstElement *appsrc;
	guint sourceid;
	guint64 num_samples = 0;
	gfloat a=0, b=1, c=0, d=1;     /* For waveform generation */
}CustomData2;
gboolean push_data(CustomData2 *data) {
	const int BUFFER_BYTE_LENGTH = 1024;
	const int NUM_SAMPLES = BUFFER_BYTE_LENGTH / 2;
	GstBuffer *buffer = gst_buffer_new_and_alloc(BUFFER_BYTE_LENGTH);
	GST_BUFFER_TIMESTAMP(buffer) = gst_util_uint64_scale(data->num_samples, GST_SECOND, 44100);
	GST_BUFFER_DURATION(buffer) = gst_util_uint64_scale(NUM_SAMPLES, GST_SECOND, 44100);

	GstMapInfo info;
	gboolean ret = gst_buffer_map(buffer, &info, GST_MAP_WRITE); assert(ret);
	gint16 *raw = (gint16*)info.data;
	data->c += data->d;
	data->d -= data->c / 1000;
	gfloat freq = 1100 + 1000 * data->d;
	for (int i = 0; i < NUM_SAMPLES; i++) {
		data->a += data->b;
		data->b -= data->a / freq;
		raw[i] = (gint16)(500 * data->a);
	}
	gst_buffer_unmap(buffer, &info);
	data->num_samples += NUM_SAMPLES;

	GstFlowReturn gstret;
	g_signal_emit_by_name(data->appsrc, "push-buffer", buffer, &gstret);
	gst_buffer_unref(buffer);
	return gstret == GST_FLOW_OK;
}
void need_data(GstElement* object, guint size, CustomData2 *data) {
	if (data->sourceid == 0) {
		data->sourceid = g_idle_add((GSourceFunc)&push_data, data);
	}
}

void enough_data(GstElement* object, CustomData2 *data) {
	if (data->sourceid != 0) {
		g_source_remove(data->sourceid);
		data->sourceid = 0;
	}
}

GstFlowReturn new_sample(GstElement* object, CustomData2 *data) {
	//收到sample
	GstSample *sample = 0;
	g_signal_emit_by_name(object, "pull-sample", &sample);
	if (sample) {
		g_print("*");
		GstBuffer *buffer = gst_sample_get_buffer(sample);
		GstSegment *segment = gst_sample_get_segment(sample);
		const GstStructure *structure = gst_sample_get_info(sample);
		GstMapInfo info;
		gboolean b = gst_buffer_map(buffer, &info, GST_MAP_READ); assert(b);
		gst_buffer_unmap(buffer, &info);
		gst_sample_unref(sample);
		return GST_FLOW_OK;
	}
	else {
		return GST_FLOW_ERROR;
	}
}

static void cb_message(GstBus *bus, GstMessage *msg, CustomData *data) {
	switch (GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_ERROR:
		g_print("GST_MESSAGE_ERROR \n");
		break;
	case GST_MESSAGE_EOS:
		g_print("GST_MESSAGE_EOS \n");
		break;
	case GST_MESSAGE_BUFFERING:
		g_print("GST_MESSAGE_BUFFERING \n");
		break;
	case GST_MESSAGE_CLOCK_LOST:
		g_print("GST_MESSAGE_CLOCK_LOST \n");
		break;
	default:
		//g_print("GST_MESSAGE %d \n", GST_MESSAGE_TYPE(msg));
		break;
	}
}

void test2() {
	/*
		apppsrc->tee->queue->audioconvert->audioresample->autoaudiosink
		            ->queue->audioconvert->wavescope->videoconvert->autovideosink
					->queue->appsink
	*/
	GstElement *appsrc = gst_element_factory_make("appsrc", 0);
	GstElement *tee = gst_element_factory_make("tee", 0);

	GstElement *queue1 = gst_element_factory_make("queue", 0);
	GstElement *audioconvert = gst_element_factory_make("audioconvert", 0);
	GstElement *audioresample = gst_element_factory_make("audioresample", 0);
	GstElement *autoaudiosink = gst_element_factory_make("autoaudiosink", 0);

	GstElement *queue2 = gst_element_factory_make("queue", 0);
	GstElement *audioconvert2 = gst_element_factory_make("audioconvert", 0);
	GstElement *wavescope = gst_element_factory_make("wavescope", 0);
	GstElement *videoconvert = gst_element_factory_make("videoconvert", 0);
	GstElement *autovideosink = gst_element_factory_make("autovideosink", 0);

	GstElement *queue3 = gst_element_factory_make("queue", 0);
	GstElement *appsink = gst_element_factory_make("appsink", 0);

	GstElement *pipeline = gst_pipeline_new("test-pipeline");

	CustomData2 data;
	data.appsrc = appsrc;
	data.sourceid = 0;

	GstAudioInfo info;
	gst_audio_info_set_format(&info, GST_AUDIO_FORMAT_S16, 44100, 2, NULL);
	GstCaps *audio_caps = gst_audio_info_to_caps(&info);
	g_object_set(appsrc, "caps", audio_caps, "format", GST_FORMAT_TIME, NULL);
	g_signal_connect(appsrc, "need-data", G_CALLBACK(&need_data), &data);
	g_signal_connect(appsrc, "enough-data", G_CALLBACK(&enough_data), &data);

	g_object_set(appsink, "emit-signals", TRUE, "caps", audio_caps, NULL);
	g_signal_connect(appsink, "new-sample", G_CALLBACK(&new_sample), &data);
	gst_caps_unref(audio_caps);

	gst_bin_add_many(GST_BIN(pipeline), appsrc, tee,
		queue1, audioconvert, audioresample, autoaudiosink,
		queue2, audioconvert2, wavescope, videoconvert, autovideosink,
		queue3, appsink, NULL);
	gboolean ret = gst_element_link_many(appsrc, tee, NULL); assert(ret);
	ret = gst_element_link_many(queue1, audioconvert, audioresample, autoaudiosink, NULL); assert(ret);
	ret = gst_element_link_many(queue2, audioconvert2, wavescope, videoconvert, autovideosink, NULL); assert(ret);
	ret = gst_element_link_many(queue3, appsink, NULL); assert(ret);

	GstPad *tee_audio_pad = gst_element_get_request_pad(tee, "src_%u");
	GstPad *queue_audio_pad = gst_element_get_static_pad(queue1, "sink");
	GstPadLinkReturn pad_return = gst_pad_link(tee_audio_pad, queue_audio_pad); assert(pad_return == GST_PAD_LINK_OK);

	GstPad *tee_audio_pad2 = gst_element_get_request_pad(tee, "src_%u");
	GstPad *queue_audio_pad2 = gst_element_get_static_pad(queue2, "sink");
	pad_return = gst_pad_link(tee_audio_pad2, queue_audio_pad2); assert(pad_return == GST_PAD_LINK_OK);

	GstPad *tee_audio_pad3 = gst_element_get_request_pad(tee, "src_%u");
	GstPad *queue_audio_pad3 = gst_element_get_static_pad(queue3, "sink");
	pad_return = gst_pad_link(tee_audio_pad3, queue_audio_pad3); assert(pad_return == GST_PAD_LINK_OK);
	gst_object_unref(queue_audio_pad); gst_object_unref(queue_audio_pad2); gst_object_unref(queue_audio_pad3);

	gst_element_set_state(pipeline, GST_STATE_PLAYING);

	GstBus *bus = gst_element_get_bus(pipeline);
	gst_bus_add_signal_watch(bus);
	g_signal_connect(bus, "message", G_CALLBACK(&cb_message), &data);

	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	gst_element_release_request_pad(tee, tee_audio_pad);
	gst_element_release_request_pad(tee, tee_audio_pad2);
	gst_element_release_request_pad(tee, tee_audio_pad3);
	gst_object_unref(tee_audio_pad);
	gst_object_unref(tee_audio_pad2);
	gst_object_unref(tee_audio_pad3);

	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
}
struct CustomData3 {
	GstElement *pipeline;
	GMainLoop *loop;
};
static void cb_message3(GstBus *bus, GstMessage *msg, CustomData3 *data) {
	switch (GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_ERROR:
		g_print("GST_MESSAGE_ERROR \n");
		gst_element_set_state(data->pipeline, GST_STATE_READY);
		g_main_loop_quit(data->loop);
		break;
	case GST_MESSAGE_EOS:
		g_print("GST_MESSAGE_EOS \n");
		gst_element_set_state(data->pipeline, GST_STATE_READY);
		g_main_loop_quit(data->loop);
		break;
	case GST_MESSAGE_BUFFERING:{
		g_print("GST_MESSAGE_BUFFERING \n");
		gint percent = 0;
		gst_message_parse_buffering(msg, &percent);
		if (percent < 100) {
			gst_element_set_state(data->pipeline, GST_STATE_PAUSED);
		}
		else {
			gst_element_set_state(data->pipeline, GST_STATE_PLAYING);
		}
	}break;
	case GST_MESSAGE_CLOCK_LOST:
		g_print("GST_MESSAGE_CLOCK_LOST \n");
		gst_element_set_state(data->pipeline, GST_STATE_PAUSED);
		gst_element_set_state(data->pipeline, GST_STATE_PLAYING);
		break;
	default:
		//g_print("GST_MESSAGE %d \n", GST_MESSAGE_TYPE(msg));
		break;
	}
}
void test3() {
	GstElement *pipeline = gst_parse_launch("uridecodebin uri=file:///d:/v1080.mp4 name=demux ! queue !glimagesink name=videosink demux. !queue !audioconvert !audioresample !autoaudiosink name=audiosink", NULL);
	//GstElement *pipeline = gst_parse_launch("playbin name=abcd uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);
	GstElement *element = gst_bin_get_by_name(GST_BIN(pipeline), "videosink");
	auto f = GST_IS_VIDEO_OVERLAY(element);
	GstVideoOverlay*overlay= GST_VIDEO_OVERLAY(element);
	auto fe = GST_IS_VIDEO_OVERLAY(overlay);
	gst_object_unref(element);

	GstBus *bus = gst_element_get_bus(pipeline);
	GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING); 
	bool islive = ret == GST_STATE_CHANGE_NO_PREROLL;

	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	CustomData3 data;
	data.pipeline = pipeline;
	data.loop = loop;
	
	gst_bus_add_signal_watch(bus);
	g_signal_connect(bus, "message", G_CALLBACK(&cb_message3), &data);
	g_main_loop_run(loop);

	g_main_loop_unref(loop);
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
}

int main()
{
 	gst_init(NULL, NULL);
	//test();
	//test2();
	test3();
	gst_deinit();
	return 0;
}