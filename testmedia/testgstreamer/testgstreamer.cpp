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
		sink_pad = gst_element_get_static_pad(data->filter_audio, "sink");
	}
	else {
		assert(false);
	}

	//gst_pad_get_current_caps(pad);
	if (GST_PAD_LINK_FAILED(gst_pad_link(pad, sink_pad))) {
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

int main()
{
 	gst_init(NULL, NULL);
	GstElementFactory *source_factory = gst_element_factory_find("uridecodebin");
	GstElement *source = gst_element_factory_create(source_factory, "source");
	GstElement *filter = gst_element_factory_make("timeoverlay", "filter");
	GstElement *sink = gst_element_factory_make("autovideosink", "sink");
	GstElement *filter_audio = gst_element_factory_make("audioconvert", "convert");
	GstElement *filter_resample = gst_element_factory_make("audioresample", "resample");
	GstElement *sink_audio = gst_element_factory_make("autoaudiosink", "sink_audio");

	GstElement *pipeline = gst_pipeline_new("test-pipeline");
	g_print("test\n");

	gst_bin_add_many(GST_BIN(pipeline), source, 
		filter, sink, 
		filter_audio, filter_resample, sink_audio,
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
	if (!gst_element_link_many(filter_audio, filter_resample, sink_audio, NULL)) {
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
	g_signal_connect(source, "pad-added", G_CALLBACK(&pad_added_handler), &data);
#endif


	GstStateChangeReturn ret = GST_STATE_CHANGE_FAILURE;
	if (GST_STATE_CHANGE_FAILURE == (ret = gst_element_set_state(pipeline, GST_STATE_PLAYING))) {
		gst_object_unref(pipeline);
		return -1;
	}

	GstBus *bus = gst_element_get_bus(pipeline);
	gboolean terminate = FALSE;
	do
	{
		GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_STATE_CHANGED));

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
				}
				break;
			default:
				break;
			}
			gst_message_unref(msg);
		}else{
			terminate = TRUE;
		}
	} while (!terminate);
	
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
	gst_object_unref(source_factory);
	return 0;
}