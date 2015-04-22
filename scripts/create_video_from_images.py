#!/usr/bin/env python

import sys
import os
import argparse
import tempfile
import subprocess
import datetime

import numpy as np
import matplotlib.pyplot as plt

image_extension = '.png'
video_encoding = '-c:v libx264 -crf 20'

def plot_timestamps(stamps, stamps_delta):
  fig = plt.figure(figsize=(8,5))
  ax = fig.add_subplot(111)
  ax.set_ylabel('delta_t')
  ax.plot(stamps[:-1], stamps_delta, 'k.')
  plt.show()


def analyze_timestamps(stamps, stamps_delta):
  mean = np.mean(stamps_delta)
  std = np.std(stamps_delta)
  print('Average delta: %s' % mean)
  print('Standard deviation: %s' % std)
  duration = stamps[-1] - stamps[0]
  print('Duration: %s' % datetime.timedelta(seconds=duration))


def imgname2timestamp(img):
  return float(os.path.basename(img).rstrip(image_extension))


def create_video(imagedir, images, durations, outputfile):
  concat_input_file = tempfile.NamedTemporaryFile(delete=False)
  for (img,dur) in zip(images, durations):
    concat_input_file.write("file '%s/%s'\n" % (imagedir, img))
    concat_input_file.write("duration %s\n" % (dur))
  concat_input_filename = concat_input_file.name
  concat_input_file.close()

  subprocess.call("ffmpeg -f concat -i %s %s %s" % (concat_input_filename, video_encoding, outputfile), shell=True)
  video_duration=subprocess.check_output("ffprobe -i %s -show_format -v quiet | sed -n 's/duration=//p'" % outputfile, shell=True)
  print('Duration of encoded video: %s' % video_duration)
  

def main():
  parser = argparse.ArgumentParser()
  #parser.add_argument('images', metavar='image', nargs='+', help='Images timestamped images to create video from')
  parser.add_argument('dir', help='Directory containing timestamped image files')
  parser.add_argument('videofile', help='Output video file')
  args = parser.parse_args()

  images=sorted(img for img in os.listdir(args.dir) if img.endswith(image_extension))
  timestamps = [imgname2timestamp(img) for img in images]
  timestamps_delta = [t2 - t1 for (t1,t2) in zip(timestamps, timestamps[1:])]
  analyze_timestamps(timestamps, timestamps_delta)
  #plot_timestamps(timestamps, timestamps_delta)
  create_video(args.dir, images, timestamps_delta, args.videofile)


if __name__ == '__main__':
  main()
