/*
The MIT License

Copyright (c) 2019-Present, ROBERT HOWELL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _DSD_API_H
#define _DSD_API_H

#include "DsdDriver.h"

#define DSD_FALSE                                                   0
#define DSD_TRUE                                                    1

#define DSD_RESULT_SUCCESS                                          0x00000000
#define DSD_RESULT_API_NOT_IMPLEMENTED                              0x00000001

/**
 * Clock Object Return Values
 */
#define DSD_RESULT_CLOCK_RESULT                                     0x00010000
#define DSD_RESULT_CLOCK_NAME_NOT_UNIQUE                            0x00010001
#define DSD_RESULT_CLOCK_NAME_NOT_FOUND                             0x00010010
#define DSD_RESULT_CLOCK_NAME_BAD_FORMAT                            0x00010011

/**
 * Source Object Return Values
 */
#define DSD_RESULT_SOURCE_RESULT                                    0x00100000
#define DSD_RESULT_SOURCE_NAME_NOT_UNIQUE                           0x00100001
#define DSD_RESULT_SOURCE_NAME_NOT_FOUND                            0x00100010
#define DSD_RESULT_SOURCE_NAME_BAD_FORMAT                           0x00100011
#define DSD_RESULT_SOURCE_NEW_EXCEPTION                             0x00100100

/**
 * StreamMux Object Return Values
 */
#define DSD_RESULT_STREAMMUX_RESULT                                 0x00110000
#define DSD_RESULT_STREAMMUX_NAME_NOT_UNIQUE                        0x00110001
#define DSD_RESULT_STREAMMUX_NAME_NOT_FOUND                         0x00110010
#define DSD_RESULT_STREAMMUX_NAME_BAD_FORMAT                        0x00110011
#define DSD_RESULT_STREAMMUX_NEW_EXCEPTION                          0x00110100

/**
 * Sink Object Return Values
 */
#define DSD_RESULT_SINK_RESULT                                      0x01000000
#define DSD_RESULT_SINK_NAME_NOT_UNIQUE                             0x01000001
#define DSD_RESULT_SINK_NAME_NOT_FOUND                              0x01000010
#define DSD_RESULT_SINK_NAME_BAD_FORMAT                             0x01000011
#define DSD_RESULT_SINK_NEW_EXCEPTION                               0x01000100

/**
 * OSD Object Return Values
 */
#define DSD_RESULT_OSD_RESULT                                       0x01010000
#define DSD_RESULT_OSD_NAME_NOT_UNIQUE                              0x01010001
#define DSD_RESULT_OSD_NAME_NOT_FOUND                               0x01010010
#define DSD_RESULT_OSD_NAME_BAD_FORMAT                              0x01010011
#define DSD_RESULT_OSD_NEW_EXCEPTION                                0x01010100

/**
 * GIE Object Return Values
 */
#define DSD_RESULT_GIE_RESULT                                       0x01100000
#define DSD_RESULT_GIE_NAME_NOT_UNIQUE                              0x01100001
#define DSD_RESULT_GIE_NAME_NOT_FOUND                               0x01100010
#define DSD_RESULT_GIE_NAME_BAD_FORMAT                              0x01100011
#define DSD_RESULT_GIE_NEW_EXCEPTION                                0x01100100

/**
 * Display Object Return Values
 */
#define DSD_RESULT_DISPLAY_RESULT                                   0x10000000
#define DSD_RESULT_DISPLAY_NAME_NOT_UNIQUE                          0x10000001
#define DSD_RESULT_DISPLAY_NAME_NOT_FOUND                           0x10000010
#define DSD_RESULT_DISPLAY_NAME_BAD_FORMAT                          0x10000011
#define DSD_RESULT_DISPLAY_NEW_EXCEPTION                            0x10000100

/**
 * Pipeline Object Return Values
 */
#define DSD_RESULT_PIPELINE_RESULT                                  0x11000000
#define DSD_RESULT_PIPELINE_NAME_NOT_UNIQUE                         0x11000001
#define DSD_RESULT_PIPELINE_NAME_NOT_FOUND                          0x11000010
#define DSD_RESULT_PIPELINE_NAME_BAD_FORMAT                         0x11000011
#define DSD_RESULT_PIPELINE_STATE_PAUSED                            0x11000100
#define DSD_RESULT_PIPELINE_STATE_RUNNING                           0x11000101
#define DSD_RESULT_PIPELINE_NEW_EXCEPTION                           0x11000110
#define DSD_RESULT_PIPELINE_COMPONENT_ADD_FAILED                    0x11000111

#define DSD_SOURCE_TYPE_CAMERA_V4L2                                 1
#define DSD_SOURCE_TYPE_URI                                         2
#define DSD_SOURCE_TYPE_MULTI_URI                                   3
#define DSD_SOURCE_TYPE_RTSP                                        4
#define DSD_SOURCE_TYPE_CSI                                         5

#define DSD_SINK_TYPE_FAKE                                          1
#define DSD_SINK_TYPE_EGL                                           2
#define DSD_SINK_TYPE_FILE                                          3
#define DSD_SINK_TYPE_RTSP                                          4
#define DSD_SINK_TYPE_CSI                                           5

/**
 * @brief creates a new, uniquely named Source obj
 * @param source unique name for the new Source
 * @param type value of DSD_SOURCE_TYPE
 * @param live specifies if source is live [DSD_TRUE | DSD_FLASE]
 * @param width width of the source in pixels
 * @param height height of the source in pixels
 * @param fps-n
 * @param fps-d
 * @return DSD_RESULT_SOURCE_RESULT
 */
DsdReturnType dsd_source_new(const std::string& source, guint type, 
    gboolean live, guint width, guint height, guint fps_n, guint fps_d);

/**
 * @brief deletes a Source object by name
 * @param source name of the Source object to delete
 * @return DSD_RESULT_SOURCE_RESULT
 */
DsdReturnType dsd_source_delete(const std::string& source);

/**
 * @brief creates a new, uniquely named Streammux obj
 * @param streammux unique name for the new Streammux obj
 * @param live DSD_TRUE | DSD_FLASE
 * @param batchSize
 * @param batchTimeout
 * @param width width of the muxer output
 * @param heigth height of the muxer output
 * @return DSD_RESULT_STREAMMUX_RESULT
 */
DsdReturnType dsd_streammux_new(const std::string& streammux, 
    gboolean live, guint batchSize, guint batchTimeout, guint width, guint height);

/**
 * @brief deletes a Source object by name
 * @param source name of the Source object to delete
 * @return DSD_RESULT_STREAMMUX_RESULT
 */
DsdReturnType dsd_streammux_delete(const std::string& streammux);

/**
 * @brief creates a new, uniquely named Display obj
 * @param display unique name for the new Display
 * @param rows number of horizotal display rows
 * @param columns number of vertical display columns
 * @param width width of each column in pixals
 * @param height height of each row in pix  als
 * @return DSD_RESULT_DISPLAY_RESULT
 */
DsdReturnType dsd_display_new(const std::string& display, 
    guint rows, guint columns, guint width, guint height);

/**
 * @brief deletes a Display object by name
 * @param display name of the Display object to delete
 * @return DSD_RESULT_DISPLAY_RESULT
 */
DsdReturnType dsd_display_delete(const std::string& display);

/**
 * @brief creates a new, uniquely named GIE object
 * @param gie unique name for the new GIE object
 * @param model full pathspec to the model config file
 * @param infer full pathspec to the inference config file
 * @param batchSize
 * @param boarder-box colors 1..4
 * @param height height of each row in pix  als
 * @return DSD_RESULT_GIE_RESULT
 */
DsdReturnType dsd_gie_new(const std::string& gie, 
    const std::string& model,const std::string& infer, 
    guint batchSize, guint bc1, guint bc2, guint bc3, guint bc4);

/**
 * @brief deletes a GIE object by name
 * @param display name of the Display object to delete
 * @return DSD_RESULT_GIE_RESULT
 */
DsdReturnType dsd_gie_delete(const std::string& gie);

/**
 * @brief creates a new, uniquely named Pipeline
 * @param pipeline unique name for the new Pipeline
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_new(const std::string& pipeline);

/**
 * @brief deletes a Pipeline object by name.
 * Does NOT delete the Pipeline object used to create the pipeline
 * @param pipeline unique name of the Pipeline to delete.
 * @return DSD_RESULT_PIPELINE_RESULT.
 */
DsdReturnType dsd_pipeline_delete(const std::string& pipeline);

/**
 * @brief adds a Source object to a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param source name of the Source object to add
 * @return DSD_RESULT_CONFIG_RESULT
 */
DsdReturnType dsd_pipeline_source_add(const std::string& pipeline, 
    const std::string& source);

/**
 * @brief removes a Source object from a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param source name of the Source object to remove
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_source_remove(const std::string& pipeline, 
    const std::string& source);

/**
 * @brief adds a Stream Mux object to a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param streammux name of the Source object to add
 * @return DSD_RESULT_CONFIG_RESULT
 */
DsdReturnType dsd_pipeline_streammux_add(const std::string& pipeline, 
    const std::string& streammux);

/**
 * @brief removes a Stream Mux object from a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param streammux name of the Source object to remove
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_streammux_remove(const std::string& pipeline, 
    const std::string& streammux);

/**
 * @brief adds an OSD object to a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param osd name of the OSD object to add
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_osd_add(const std::string& pipeline, const std::string& osd);

/**
 * @brief removes an OSD object from a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param osd name of the OSD object to remove
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_osd_remove(const std::string& pipeline, 
    const std::string& osd);

/**
 * @brief adds a GIE object to a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param osd name of the OSD object to add
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_gie_add(const std::string& pipeline, 
    const std::string& gie);

/**
 * @brief removes a GIE object from a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param gie name of the GIE object to remove
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_gie_remove(const std::string& pipeline, 
    const std::string& gie);

/**
 * @brief adds a GIE object to a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param display name of the Display object to add
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_display_add(const std::string& pipeline, 
    const std::string& display);

/**
 * @brief removes an OSD object from a Pipeline object
 * @param[in] pipeline name of the pipepline to update
 * @param display name of the Display object to remove
 * @return DSD_RESULT_PIPELINE_RESULT
 */
DsdReturnType dsd_pipeline_display_remove(const std::string& pipeline, 
    const std::string& display);

/**
 * @brief pauses a Pipeline if in a state of playing
 * @param pipeline unique name of the Pipeline to pause.
 * @return DSD_RESULT.
 */
DsdReturnType dsd_pipeline_pause(const std::string& pipeline);

/**
 * @brief plays a Pipeline if in a state of paused
 * @param pipeline unique name of the Pipeline to play.
 * @return DSD_RESULT_PIPELINE_RESULT.
 */
DsdReturnType dsd_pipeline_play(const std::string& pipeline);

/**
 * @brief gets the current state of a Pipeline
 * @param pipeline unique name of the Pipeline to query
 * @return DSD_RESULT_PIPELINE_PAUSED | DSD_RESULT_PIPELINE_PLAYING
 */
DsdReturnType dsd_pipeline_get_state(const std::string& pipeline);

void dsd_main_loop_run();

#endif // _DSD_API_H
