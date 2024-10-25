import subprocess

input_path = 'render/Output.mp4'
output_path = 'demo/Output.gif'

command = [
    'ffmpeg',
    '-y', 
    '-i', input_path,
    '-vf', 'fps=30,scale=730:-1:flags=lanczos',  
    '-c:v', 'gif',
    output_path
]

try:
    subprocess.run(command, check=True)
    print("GIF rendered successfully!")
except subprocess.CalledProcessError as e:
    print("An error occurred:", e)
