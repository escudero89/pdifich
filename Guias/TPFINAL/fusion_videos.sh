#!/bin/sh

% Para llamar, haces: %
% ./fusion_videos.sh video1.ext video2.ext output.extension %

ffmpeg -i $1 -vf "[in] pad=2*iw:ih [left]; movie=$2 [right]; [left][right] overlay=main_w/2:0 [out]" -b:v 3000k $3
