# MusicBox project by Peter Hoß, 2018
# WARNING: This script has not been thoroughly tested. Use at your own risk.
# USAGE: call the script and point it to a folder containing the MP3 files you want to merge and convert like so: "sh mp3towavscript.sh /path/to/folder". The script will produce a combined .mp3 file and a converted .wav file in the folder it's currently in.
# NOTE: ffmpeg is needed for this script to work. Download it at: https://ffmpeg.org/download.html

#!/bin/bash
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
