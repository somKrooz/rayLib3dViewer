import subprocess

input_path = 'render/Frame_%d.png' 
output_path = 'render/Output.mp4'  

command = [
    'ffmpeg',
    "-y", 
    '-framerate', '60',
    '-start_number', '2',  # Start from Frame_1.png
    '-i', input_path,
    '-c:v', 'libx264',
    '-preset', 'slow',  
    '-b:v', '5000k',  
    '-pix_fmt', 'yuv420p',
    output_path
]

try:
    subprocess.run(command, check=True)
    print("Video rendered successfully!")
except subprocess.CalledProcessError as e:
    print("An error occurred:", e)
