#pragma once

#include <ctime>

class Frame_Counter
{
    clock_t t_first_frame;
    clock_t t_last_frame;
    int frame_capture_time;
    int current_frame;
    float frame_rate;

public:

    /*
    Frame Counter initializer, set up the frame counter,
    frame_capture_time is the amount of frame captured to calculate the frame rate
    */
    Frame_Counter(int frame_capture_time)
    {
        t_first_frame = clock();
        t_last_frame = clock();
        this->frame_capture_time = frame_capture_time;
        current_frame = 0;
        frame_rate = 0;
    }

    /*
    The frame updater keep ontrack of the frame in the loop
    returns the frame captured
    */
    int frame_updater()
    {

        if (current_frame == frame_capture_time)
        {
            t_last_frame = clock();
            frame_rate = 1 / (float(t_last_frame - t_first_frame) / float(frame_capture_time * 100));
            t_first_frame = t_last_frame;
            current_frame = 0;

            return frame_rate;
        }

        current_frame++;

        return -1;
    }
};