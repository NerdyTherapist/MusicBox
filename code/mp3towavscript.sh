#!/bin/bash
# written by Peter Hoß, December 9, 2018
# NOTE: ffmpeg is needed for this script to work. Download it at: https://ffmpeg.org/download.html
# When calling this script, a folder/directory must be provided that contains mp3 files.


# Getting all the mp3-files in the directory and creating a concatenation string
FILENAMES="concat:";
for file in "$1"/*.mp3; do 
	FILENAMES+="$file|"
done
FILENAMES=${FILENAMES/%?}

# echo "$FILENAMES"

# concatenating all files
ffmpeg -i "$FILENAMES" -c copy combined.mp3

# converting the combined file
ffmpeg -i combined.mp3 -acodec pcm_s16le -ac 1 -ar 22050 converted.wav