// testgstreamer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include "gst/gst.h"
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

int main()
{
 	gst_init(NULL, NULL);
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
		}else{
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
	return 0;
}