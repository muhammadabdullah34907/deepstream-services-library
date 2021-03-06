################################################################################
# The MIT License
#
# Copyright (c) 2019-2020, Robert Howell. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
################################################################################

#!/usr/bin/env python

import sys
sys.path.insert(0, '../../')
from dsl import *

# Using NVIDIA's example python code an OSD Sink Pad callback function
# that addes current object metrics on the on-screen-display.
from nvidia_osd_sink_pad_buffer_probe import osd_sink_pad_buffer_probe

# Sample 360-deg video and dewarper config setting to use.
uri_file = '../../test/streams/sample_cam6.mp4'
dewarper_config_file = '../../test/configs/config_dewarper.txt'

# Filespecs for the Primary GIE
primary_infer_config_file = '../../test/configs/config_infer_primary_nano.txt'
primary_model_engine_file = '../../test/models/Primary_Detector_Nano/resnet10.caffemodel_b1_gpu0_fp16.engine'

# Filespecs for the Secondary GIE
sgie1_config_file = '../../test/configs/config_infer_secondary_carcolor_nano.txt'
sgie1_model_file = '../../test/models/Secondary_CarColor/resnet18.caffemodel_b1_gpu0_fp16.engine'

sgie2_config_file = '../../test/configs/config_infer_secondary_carmake_nano.txt'
sgie2_model_file = '../../test/models/Secondary_CarMake/resnet18.caffemodel_b1_gpu0_fp16.engine'

sgie3_config_file = '../../test/configs/config_infer_secondary_vehicletypes_nano.txt'
sgie3_model_file = '../../test/models/Secondary_VehicleTypes/resnet18.caffemodel_b1_gpu0_fp16.engine'

## 
# Function to be called on XWindow KeyRelease event
## 
def xwindow_key_event_handler(key_string, client_data):
    print('key released = ', key_string)
    if key_string.upper() == 'P':
        dsl_pipeline_pause('pipeline')
    elif key_string.upper() == 'R':
        dsl_pipeline_play('pipeline')
    elif key_string.upper() == 'Q' or key_string == '':
        dsl_main_loop_quit()
 
## 
# Function to be called on XWindow Delete event
## 
def xwindow_delete_event_handler(client_data):
    print('delete window event')
    dsl_main_loop_quit()

# Function to be called on End-of-Stream (EOS) event
def eos_event_listener(client_data):
    print('Pipeline EOS event')
    dsl_main_loop_quit()

## 
# Function to be called on every change of Pipeline state
## 
def state_change_listener(old_state, new_state, client_data):
    print('previous state = ', old_state, ', new state = ', new_state)
    if new_state == DSL_STATE_PLAYING:
        dsl_pipeline_dump_to_dot('pipeline', "state-playing")

def main(args):

    # Since we're not using args, we can Let DSL initialize GST on first call
    while True:

        # New URI File Source using the filespec defined above
        retval = dsl_source_uri_new('uri-source', uri_file, False, 0, 0, 0)
        if retval != DSL_RETURN_SUCCESS:
            break

        # New Dewarper for the (recorded) 360 deg. URI camera
        retval = dsl_dewarper_new('dewarper', dewarper_config_file)
        if retval != DSL_RETURN_SUCCESS:
            break
            
        # Add the Dewarper directly to Source component
        retval = dsl_source_decode_dewarper_add('uri-source', 'dewarper')
        if retval != DSL_RETURN_SUCCESS:
            break
        
        # New Primary GIE using the filespecs above with interval = 0
        retval = dsl_gie_primary_new('pgie', primary_infer_config_file, primary_model_engine_file, 1)
        if retval != DSL_RETURN_SUCCESS:
            break

        # New Secondary GIEs using the filespecs above with interval = 0
        retval = dsl_gie_secondary_new('carcolor-sgie', sgie1_config_file, sgie1_model_file, 'pgie', 0)
        if retval != DSL_RETURN_SUCCESS:
            break
        retval = dsl_gie_secondary_new('carmake-sgie', sgie2_config_file, sgie2_model_file, 'pgie', 0)
        if retval != DSL_RETURN_SUCCESS:
            break
        retval = dsl_gie_secondary_new('vehicletype-sgie', sgie3_config_file, sgie3_model_file, 'pgie', 0)
        if retval != DSL_RETURN_SUCCESS:
            break

        # New KTL Tracker, setting max width and height of input frame
        retval = dsl_tracker_ktl_new('ktl-tracker', 480, 272)
        if retval != DSL_RETURN_SUCCESS:
            break

        # New Tiled Display, setting width and height, use default cols/rows set by source count
        retval = dsl_tiler_new('tiler', 1280, 720)
        if retval != DSL_RETURN_SUCCESS:
            break
 
        # New OSD with clock enabled... .
        retval = dsl_osd_new('on-screen-display', True)
        if retval != DSL_RETURN_SUCCESS:
            break

        # Add Nvidia's example batch meta handler to the Source Pad of the KTL Tracker
        retval = dsl_osd_batch_meta_handler_add('on-screen-display', DSL_PAD_SINK, osd_sink_pad_buffer_probe, None)
        if retval != DSL_RETURN_SUCCESS:
            break
        
        ## New Window Sink, 0 x/y offsets and same dimensions as Tiled Display
        retval = dsl_sink_window_new('window-sink', 0, 0, 1280, 720)
        if retval != DSL_RETURN_SUCCESS:
            break

        # Add all the components to our pipeline
        retval = dsl_pipeline_new_component_add_many('pipeline', ['uri-source', 'pgie', 'ktl-tracker', 
            'carcolor-sgie', 'carmake-sgie', 'vehicletype-sgie', 'tiler', 'on-screen-display', 'window-sink', None])
        if retval != DSL_RETURN_SUCCESS:
            break

        # Add the XWindow event handler functions defined above
        retval = dsl_pipeline_xwindow_key_event_handler_add("pipeline", xwindow_key_event_handler, None)
        if retval != DSL_RETURN_SUCCESS:
            break
        retval = dsl_pipeline_xwindow_delete_event_handler_add("pipeline", xwindow_delete_event_handler, None)
        if retval != DSL_RETURN_SUCCESS:
            break

        # Add the listener callback functions defined above
        retval = dsl_pipeline_state_change_listener_add('pipeline', state_change_listener, None)
        if retval != DSL_RETURN_SUCCESS:
            break
        retval = dsl_pipeline_eos_listener_add('pipeline', eos_event_listener, None)
        if retval != DSL_RETURN_SUCCESS:
            break

        # Play the pipeline
        retval = dsl_pipeline_play('pipeline')
        if retval != DSL_RETURN_SUCCESS:
            break

        dsl_main_loop_run()
        retval = DSL_RETURN_SUCCESS
        break

        # Print out the final result
        print(dsl_return_value_to_string(retval))

    dsl_pipeline_delete_all()
    dsl_component_delete_all()

if __name__ == '__main__':
    sys.exit(main(sys.argv))
