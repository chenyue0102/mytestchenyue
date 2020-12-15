// testgstreamer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "gst/gst.h"

int main()
{
 	gst_init(NULL, NULL);
	GstElementFactory *source_factory = gst_element_factory_find("videotestsrc");
	GstElement *source = gst_element_factory_create(source_factory, "source");
	GstElement *filter = gst_element_factory_make("timeoverlay", "filter");
	GstElement *sink = gst_element_factory_make("autovideosink", "sink");

	GstElement *pipeline = gst_pipeline_new("test-pipeline");
	g_print("test\n");

	gst_bin_add_many(GST_BIN(pipeline), source, filter, sink, NULL);
	if (!gst_element_link_many(source, filter, sink, NULL)) {
		gst_object_unref(pipeline);
		return -1;
	}

	g_object_set(source, "pattern", 0, NULL);

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
				break;
			case GST_MESSAGE_EOS:
				terminate = TRUE;
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