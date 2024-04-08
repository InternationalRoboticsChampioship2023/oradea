# Tensorflow Object Detection Walkthrough

## Steps
<br />

<b>Step 1.</b> Create a new virtual environment 
<pre>
python -m venv tfod
</pre> 
<br/>
<b>Step 2.</b> Activate your virtual environment
<pre>

.\tfod\Scripts\activate # Windows 
</pre>
<br/>
<b>Step 3.</b> Install dependencies and add virtual environment to the Python Kernel
<pre>
python -m pip install --upgrade pip
pip install ipykernel
python -m ipykernel install --user --name=tfodj
</pre>

<b>Step 4.Follow the stepts in the two ipynb files, that go thru the instalation procces of the neccesary libraries, packages and some other github repositories as a side-aid, to training and evaluating the API model, traing from a generic one that can be found in Tensorflow Model Zoo Github repository, and custom tailored to this specific needs of this project.</b>
<br/>

After training and evaluating trhe model, you can check it's performance using the next command:
<pre>tensorboard --logdir=. </pre>
Tensorboard will be accessible through your browser and you will be able to see metrics including mAP - mean Average Precision, and Recall.
<br />