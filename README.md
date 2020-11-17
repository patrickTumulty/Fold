# Fold
Fold distortion plugin implemented in JUCE. 

Select between a `Linear` or `Sine` folding algorithm. Linear is a simple mirroring of the waveform once it crosses a threshold. The Sine algorithm, simply put, puts the signal through the sin function. The saturation parameter, implemented as a difference equation, dictates the balance between folding and a softclip (arctangent). 


<p align="center">
	<img src="./Images/GUI_Example.png" width="500">
</p>
