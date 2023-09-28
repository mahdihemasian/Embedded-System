#include <gst/gst.h>

int main(int argc, char *argv[]) {
  GstElement *pipeline, *src, *x264enc, *h264parse, *hlssink;
  GstCaps *caps;
  GstBus *bus;
  GstMessage *msg;
  GMainLoop *loop;

  /* Initialize GStreamer */
  gst_init(&argc, &argv);
  loop = g_main_loop_new(NULL, FALSE);

  /* Create elements */
  pipeline = gst_pipeline_new("pipeline");
  src = gst_element_factory_make("videotestsrc", "src");
  x264enc = gst_element_factory_make("x264enc", "enc");
  h264parse = gst_element_factory_make("h264parse", "parse");
  hlssink = gst_element_factory_make("hlssink2", "sink");

  /* Create caps */
  caps = gst_caps_new_simple("video/x-h264",
                             "stream-format", G_TYPE_STRING, "avc",
                             "alignment", G_TYPE_STRING, "au",
                             "profile", G_TYPE_STRING, "constrained-baseline",
                             NULL);

  /* Set properties */
  g_object_set(G_OBJECT(src), "is-live", TRUE, NULL);
  g_object_set(G_OBJECT(hlssink), "max-files", 5, NULL);
  
  /* Add elements to the pipeline */
  gst_bin_add_many(GST_BIN(pipeline), src, x264enc, h264parse, hlssink, NULL);

  /* Link elements */
  if (!gst_element_link_many(src, x264enc, h264parse, hlssink, NULL)) {
    g_printerr("Failed to link elements\n");
    return -1;
  }

  /* Set caps on the output of the encoder */
  gst_element_link_filtered(x264enc, h264parse, caps);

  /* Start the pipeline */
  gst_element_set_state(pipeline, GST_STATE_PLAYING);
  
  /* Run the main loop */
  g_main_loop_run(loop);

  /* Stop the pipeline */
  gst_element_set_state(pipeline, GST_STATE_NULL);

  /* Free resources */
  gst_object_unref(GST_OBJECT(pipeline));
  gst_caps_unref(caps);
  g_main_loop_unref(loop);

  return 0;
}
