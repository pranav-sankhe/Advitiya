# Electronics Required For HAM

Just for the sake of completion and to have a well structured flow of content, we will start from elementary concepts. 

## Atmoic Structure

### Valence Electrons

- **Conductor**
- **Insulator** 
- **Semi Conductors**

**Note** : The classification of materials into the above mentioned sections as we all know based on the band gap energy and not valence electrons. They are closely related and in layman language we can use them to explain the classification. 

#### List of very elementary concepts with which we extremely comfortable with. 
- Conductance
- Current
- Electromotive Force
- Voltage
- Ohms Law 

#### Electrical Components
- **Resistor**
	- Resistance
	- Specific Resistane
	- Standard Colour Code 

- **Capacitor**
	- Capacitance
	- Fixed and variable Capacitors

- **Inductor**
	- Inductane
	- Self and Mutual Inductance

##### Transformer

###### Auto Transformer  

###### Audio Transformer 
Used to increase the voltage of audio frequency signals.

###### Intermediate Frequency Transformer

These are mainly used to increase the voltage of IF frequency signals. They are used in IF circuits
as coupling devices and operate at frequency ranging between 450 to 460 KHz.

###### Radio Frequency Transformer 
These are used for coupling one stage of RF amplification to another.

###### Impedance Matching [Important Application of Transformer]
In the transfer of power from any electrical source of its load, the impedance of the load must be
equal to or match the internal impedance of the source for maximum transfer of power. The
transformer is a useful device for matching the impedance of a generator to that of its load. 


### AC Fundamentals 

#### Frequency 
#### Wavelength
#### Phase
#### Average and RMS value
#### Impedance
#### Power Factor
#### Resonance

**Note** : __"For a series circuit at resonance, frequencies becoming far removed from resonance see an ever
increasing impedance. For a parallel circuit at resonance, frequencies becoming far removed from
resonance see an ever decreasing impedance".__ 

### Rectifier

#### Half Wave Rectifier
#### Full Wave Rectifier
#### Bridge Rectifier
#### Smoothing or Filter Circuit
#### Capacitive Input Filter

### Electronic Voltage Regulation

When extremely low ripple is required or when the supply voltage must be constant with large fluctuations of load
current and line voltage, a closed loop amplifier is used to regulate the supply.
</br> 
There are two main categories of electronic regulators:
- Linear regulators, in which the condition of the control element is varied in direct proportion to the line
voltage or load current;

- Switching regulators, in which the control device is switched ON and OFF, with the duty cycle proportion to the line or load conditions.

#### IC Voltage Regulators
Inside each regulator is a reference, a high gain error amplifier, temperature compensated voltage sensing resistors and transistors and a pass element. 

#### Switching Regulators

#### Voltage Stabilization (Zener Diode Regulation)

### Transistor
- Emitter 
- Collector 
-Base

#### Current Amplifier 


### Amplifier

#### Class A Amplifiers

Class A amplifiers are those in which the grid bias and plate voltage are so chosen that the tube
operates over the linear portion of dynamic curve or it is an amplifier in which plate current flows
over the entire cycle.

![class_A_amp](https://github.com/sabSAThai/Advitiya/blob/master/images/class_A_amp.png)

Characteristics: 
- Waveform at the output is exactly similar to that of input. Less distortion since operated in linear region. 
- High voltage amplification
-  In practice the power output is small because both current and voltage are restricted to comparatively small variations.

#### Class B Amplifiers
These amplifiers are biased to cut-off or approximately so, hence plate current flows during
positive half cycle of the input voltage.

![class_B_amp](https://github.com/sabSAThai/Advitiya/blob/master/images/class_B_amp.png)

Characteristics : 
- High distortions, Less amplification 
- High power output 


#### Class ‘AB’ Amplifier 

The grid bias and signal voltages are so adjusted that the plate current flows for more than half and
less than entire cycle. The characteristic of this amplifier lie in between those of class A’ and class
‘B amplifiers.

#### Class ‘D’ Amplifier

In these type of amplifiers the tube s biased beyond cut off point, the grid bias is as much as twice
the cut off value. Hence the plate current flows in pulses of less than one half cycle.

![class_C_amp](https://github.com/sabSAThai/Advitiya/blob/master/images/class_C_amp.png)

Characteristics :
- Very high distortion. Low amplification 
- Power output per tube is higher as compared to class B’ amplifier. 

**Note** : These amplifiers are not used as audio frequency amplifiers because of high distortion. But they are
used as radio frequency amplifiers for high power output.

#### Push-Pull Amplifier 

To increase power amplification, two transistors are used in push pull arrangements in the output stage. One transistor amplifies the +ve half cycle of the signal while the other transistor amplifies the -ve half cycle of the signal.
</br>
Push pull arrangement: when one Transistor is pushing (conduction), the other is pulling (stopping
conduction).

Characteristics: High power amplification. 

#### Distortions in amplifiers :

- Nonlinear Harmonic Distortion 
- Frequency Distortion 
- Phase Distortion 


### Transistor Amplifiers
Amplifier circuits used with transistors fall into one of three types, known as the common-base,
common-emitter and common-collector circuits. 

#### Common Base Circuit

![common_base.png](https://github.com/sabSAThai/Advitiya/blob/master/images/common_base.png)

Characteristics: 
- The input circuit of a common-base amplifier must be designed for low impedance. 
- The optimum output load impedance, RL may range from a few thousand ohms to 100,000.
-  In this circuit the phase of the output (collector) current is
the same as that of the input emitter) current.  


#### Common Emitter Circuit

![common_emitter.png](https://github.com/sabSAThai/Advitiya/blob/master/images/common_emitter.png)

Characteristics: 

- The base current is small and the input impedance is therefore fairly high- several thousand ohms in the average case. 
-  The collector resistance is some tens of thousands of ohms, depending on the signal source impedance.

#### Common Collector Circuit

![common_collector.png](https://github.com/sabSAThai/Advitiya/blob/master/images/common_collector.png)

Characteristics : 
- The input resistance depends on the load resistance.
-  The output and input currents are in phase.


### Oscillator

#### Hartley Oscillator, Colpitt's Oscillator
- Based on L-C oscillations. 

#### Piezoelectric Effect
- Certain crystalline materials when we apply an AC voltage across them, they vibrate at the frequency of the applied voltage. Conversely, when they are compressed or placed under mechanical strain to vibrate, they
produce an AC voltage. Of the various piezoelectric crystals, quartz is most commonly used because it is
inexpensive and readily available in nature.

#### Transistor Crystal Oscillator

![transistor_crystal.png](https://github.com/sabSAThai/Advitiya/blob/master/images/transistor_crystal.png)

A tank circuit L1-C1 is placed in the collector and the crystal is connected in the base circuit.
Feedback is obtained by coil L2 inductively coupled to coil Li. The crystal is connected in series
with the feedback winding. The natural frequency of L C circuit is made nearly equal to the natural
frequency of crystal.

**Advantages**
1) They have a high order of frequency stability.
2) The quality factor Q of the crystal is very high. It is high as 10,000 compared to about 100 of LC
tank.

**Disadvantages**
1) They are used in low power circuits.
2) The frequency of oscillators cannot be changed.



##  Modulation 

The audio frequency signals cannot be radiated out from the aerial directly because transmission at
audio frequencies is not practical. For this purpose oscillations of very high frequency or radio
frequency are produced with the help of oscillators. These electromagnetic waves so produced are
of constant amplitude and of extremely high frequencies. The audio frequency signal is then super
imposed on the RF waves which are known as Carrier waves (because they carry AF signals
through space to distant places). The process by which AF signal is super imposed on the Carrier
wave is known as Modulation.

There are three types of Modulations, namely

- Amplitude Modulation
- Frequency Modulation
- Phase Modulation


### Amplitude Modulation
A method of transmission and reception of radio waves in which the amplitude of the carrier wave
is made to vary in accordance with the audio frequency wave.

![AM.png](https://github.com/sabSAThai/Advitiya/blob/master/images/AM.png)

### Frequency Modulation 

In this method the carrier wave is modulated by changing its frequency in relation to the AF signal without changing its amplitude. This process is known as frequency modulation (FM).

![FM.png](https://github.com/sabSAThai/Advitiya/blob/master/images/FM.png)

#### Phase Modulation

A method of conveying information via radio frequency carrier waves in which the instantaneous
phase of the carrier is shifted in accordance with the audio frequency wave. Phase Modulation is
very similar to FM wave.

![PM.png](https://github.com/sabSAThai/Advitiya/blob/master/images/PM.png)



### Major Modulation Systems
The broadcast category of modulation systems is how the main carrier is modulated. 

The major types are:  
- Amplitude modulation
- Angle modulation 
- Pulse modulation


#### Angle Modulation

Two particular forms of angle modulation are frequency Modulation (FM) and Phase Modulation
(PM). The term frequency modulation is often used to cover various forms of angle modulation.
</br>
Frequency and Phase modulations are not independent, since the frequency cannot be
varied without also varying the phase, and vice versa. The communications effectiveness of FM
and PM depends almost entirely on the receiving methods. If the receiver will respond to frequency
and phase changes but is insensitive to amplitude changes, it will discriminate against most forms
of noise, particularly impulse noise such as that from ignition systems.


#### Pulse Modulation



### Demodulation

Demodulation is the process of deriving the original modulation signal from a modulated carrier
wave. The received signal usually contains noise and distortion picked up along the way.
Demodulation is part of the receiving process and is performed in a demodulator. 


## Radio Receiver
A radio receiver is an electronic device that takes a transmitted signal, extracts the original signal
from it and amplifies that signal.

#### Characteristics of Receiver

##### Sensitivity
The ability of a radio receiver to pick up and reproduce weak radio signals is called sensitivity. The
sensitivity of a radio receiver is determined by the value of high frequency voltage that must be fed
to its input circuit (between the aerial earth terminals) in order to secure a normal output power i.e.
to secure a normal reception. The lower is such input voltage necessary for the normal reception;
the higher is the receiver sensitivity.

##### Selectivity
The ability of a radio receiver to separate the signal of a required radio station from the signals of
unwanted stations, operating on other frequencies, is called selectivity. 
The selectivity of a radio receiver depends upon the number and the quality of tuned circuits
employed by the receiver. The greater the number of tuned circuits adjusted to resonance in a radio
receive and the higher the quality of such tuned circuits, the higher is the selectivity at such a receiver.

##### Fidelity

It can be defined as the quality or precision with which the output is reproduced or (The lower the
distortion introduced by a radio receiver, the higher is the quality of reproduction or fidelity of such
a receiver.)

##### Stability

Stability may be defined as a measure of the ability of a radio receiver to deliver a constant amount
of output for a given period of time when the receiver is supplied with a signal of constant
amplitude and frequency. 


### Tuned Radio Frequency (TRF) Receiver

The general design principle of a T R F receiver is shown in the block diagram below

![TRF.png](https://github.com/sabSAThai/Advitiya/blob/master/images/TRF.png)

- The radio frequency waves picked up by the aerial are first fed to the tuned input circuit of the
receiver this circuit being coupled to the aerial.
- The input circuit tuned to the frequency of the incoming signal, provides a certain amount of amplification and also gives some preliminary selectivity, separating the signal of a desired radio station from the signals of numerous other stations simultaneously picked up by the receiving aerial.
- The radio frequency voltage built up across the tuned circuit at the input of the receiver is then
applied to the first stage of RF amplification. The RF amplifier usually consists of not more than
two stages.
- Having passed through the RE amplifier, the amplified RF signal reaches the detector stage where
it is rectified.
- The low frequency (audio frequency) signal developed at the output of the detector is, next,
amplified in AF amplifier stages. The output of AF amplifier feeds the loudspeaker or a pair of
earphones.



#### Super Heterodyne Receiver

![hetero_receiver.png](https://github.com/sabSAThai/Advitiya/blob/master/images/hetero_receiver.png)

**RF amplifier stage**
The radio waves from various broadcasting stations are intercepted by the
receiving aerial and are coupled to this stage. This stage selects the desired radio wave (using a
tuned circuit) and raises the strength of the wave to the desired level.

**Mixer stage**
The amplified output of RF amplifier is fed to the mixer stage where it is combined
with the output of a local oscillator. The two frequencies beat together and produce an intermediate
frequency (IF). 

**Local Oscillator**
The locally generated oscillations in a superhetrodyne receiver are usually of a frequency higher than the frequency of the incoming signals.

**IF amplifier stage**  
The output of mixer is always 455 kHz and is fed to fixed tuned IF amplifiers.
These amplifiers are tuned to one frequency (i.e. 455 kHz) and render nice amplification.

**Detector Stage**
Here, the audio signal is extracted from the IF output. Usually, diode detector circuit is used
because of its low distortion and excellent audio fidelity.

![AM_diode.png](https://github.com/sabSAThai/Advitiya/blob/master/images/AM_diode.png)

The rectified modulated wave contains radio frequency and the signal and cannot be fed to the
speaker for sound reproduction. The RF Component is filtered by the capacitor C shunted
across the speaker. The result is that the RF components are by-passed by the capacitor C and the signal is passed on to the speaker for sound reproduction. 

**AF amplifier stage**
The audio signal output of detector stage is fed to a multistage audio
amplifier. Here, the signal is amplified until it is sufficiently strong to drive the speaker.


#### Advantages of a Superheterodyne Receiver over T.R.F

- The Superhetrodyne receiver is having good sensitivity. This is because of the fact that the
signal, after the frequency conversion is amplified at a single and convenient, frequency for
amplification.
-  The selectivity is good as the IF amplifier stages use tuned stages with good selectivity and
required bandwidth.
- Continuous tuning is limited to the three tuned circuits namely the R.F. amplifier, Mixer
(frequency converter) and the local oscillator. 
-  The fidelity of the receiver will be better as the band with of the I. F amplifier is of the required
value.
- The R.F amplifier stage improves signal to noise ratio, reduces I.E interference and it offers a
better coupling between antenna and the input of the receiver


## Communication Receiver

![com_receiver.png](https://github.com/sabSAThai/Advitiya/blob/master/images/com_receiver.png)


It uses the principle of Superhetrodyne reception. In addition it uses two stages of mixers, with two
local oscillators The two mixers produce different intermediate frequencies. The first block indicates the special provisions for the antenna coupling circuit.
</br>
The first block indicates the special provisions for the antenna coupling circuit. It is
followed by a stage of RF amplification. 
</br>
The output of the RF amplifier goes to the mixer. The
local oscillator supplies the required frequency to get the intermediate to the second mixer stage
where another frequency conversion takes place.  
</br>
The second mixer is provided with a crystal local oscillator, which does not suffer from frequency drift.
</br>
The beat frequency oscillator, provided to Detector stage which can be switched in to the circuit or switched off.



### Some Salient features of a Communication Receiver 
- A rotary switch or the like will be provided for the selection of the frequency band.
- It is provided with a high gain RF amplifier stage An RF gain control is also provided. 
- Communication receivers are provided with amplified and delayed AGC.
- The selectivity of the receiver is adjustable.
- The second mixer is provided with a fixed frequency crystal oscillator as the local oscillator. 
- A noise limiter circuit is provided with the inter-channel noise suppressor, or muting circuit.
- Automatic frequency control circuit and a tuning indicator is provided.

###### Noise Limiter
###### Tuning Detector
###### Muting Circuit
The other names for this circuit arrangement are, inter channel noise suppressor. 

###### Beat frequency Oscillator
Beat frequency oscillator or BFO is a dedicated oscillator used to create an audio frequency signal from Morse code[pulse modulated RF carrier.] radiotelegraphy (CW) transmissions to make them audible.

###### Automatic Gain Control 
Automatic gain control is necessary in communication receivers because of the wide variations in signal strength encountered at the antenna terminal. The job of the A.G.C is to increase the gain on weak signals, and
then decrease it on strong signals. 

###### Squelch
 It enables the receiver’s output to
remain cut off unless the carrier is present Apart from eliminating inconvenience, such a system naturally increases the efficiency of the operator. Squelch is also called Muting or Quieting. We need Squelch because AGC disappears in the absence of any carrier.

###### Automatic Volume Control 
The purpose served by the automatic gain control sometimes referred to as automatic volume control is as follows. This control automatically equalizes the amplification of the radio receiver when the level of the incoming radio signal varies as a result of fading.

###### Image Interference or Image Frequency Signals

###### Signal to Noise Ratio 

###### Adjacent Channel Interference
To reduce adjacent channel interference select higher value of IF preferably between 450 KHz to 470 KHz.

###### Receiver Noise
Because of the greater number of valves employed by superhetrodyne receivers and because of the greater gain provided
by such receivers, the internal noise is much higher in a superhetrodyne receiver than in a T.R.F. Receiver.


## Transmitter
An electronic device that generates and amplifies a carrier wave, modulates it with a signal derived
from speech or from other sources and then radiates the resulting signal from the antenna.
</br>
An oscillator generates the signal and it is then amplified to raise the power output to the desired
level. A Morse key is used to chop the transmission up into the dots and dashes of Morse code.
Oscillators Morse Code. 
</br>
The oscillator runs continuously. The Driver/Buffer are isolation stages, to isolate the oscillator
from the sudden load-changes

![transmitter.png](https://github.com/sabSAThai/Advitiya/blob/master/images/transmitter.png)

### AM Transmitter 

![AM_transmitter.png](https://github.com/sabSAThai/Advitiya/blob/master/images/AM_transmitter.png)

**Microphone**
The function of a microphone is to convert the variations in air pressure produced by the human
voice or a musical instrument into the electrical voltage or current of the same frequency and
corresponding amplitude.

**RF Oscillator**
It produces RF carrier wave. 

**RF Buffer Amplifier**
It is used to increase the power and isolate the oscillator. A Stage of amplification is placed between the oscillator and the antenna or following stages. This is called Buffer Amplifier. This results in Isolating and reducing the load of the Oscillator and increased stability.


**Modulator**
The modulator section is essentially an audio amplifier. The speech amplifiers are of the voltage
type, while the modulator being basically a power amplifier. The modulator delivers the required
amount undistorted audio power to the modulator RF amplifier.

**RF Power Amplifier**
The final stage of a transmitter is the power amplifier. 

### SSB Transmitter 

![SSB.png](https://github.com/sabSAThai/Advitiya/blob/master/images/SSB.png)

We know that both sidebands of an amplitude modulated signal contain all of the intelligence being
transmitted. So, to recover the intelligence, all that is required is one sideband and the carrier. If one
of the sidebands therefore was removed from the modulator carrier immediately after modulation, it
would have no harmful effects on the transmission of the intelligence. The intelligence would be
transmitted in the other sideband, and the unmodulated carrier would accompany it for later use in
converting the intelligence to its original lower frequency.
</br>
This technique of removing one sideband from an amplitude modulated signal is called single
sideband modulation (SSB)
</br>
The most important advantage to be gained by eliminating one side band is that the bandwidth of the signal is cut in half.
</br>
Narrower the bandwidth, the less atmospheric noise, or static, that will enter the receiving circuits
with the signal. Also it each carrier uses less bandwidth in a given range, more carrier signals can be sent, or there will be less interference between different carrier signals. 

### Comparison Between AM & FM

#### AM
- It has only two side bands LSB: Fc-Fm USB: Fc+Fm
- In an AM the amplitude of the carrier is varied but frequency remains constant
- Modulation Index is independent of modulating frequency.
- Transmitted power by the AM includes carrier power and side bands power.
- Thus it needs more modulation power.
- Increased modulation index increases the total transmitted power.
- Noise is more in the AM so fidelity is less.
- Mainly used for mono transmission.


#### FM
- It has infinite number of sidebands. They are separated by Fm, 2Frn, 3Fm and so on from the
carrier frequency.
- In the FM, the frequency of the carrier is varied but amplitude of the carrier remains constant.
- Modulation index is inversely proportion to the modulating frequency.
- It needs less modulation power. Increased modulation index increases the band width but
transmitted power remains constant.
- Noise is less in the FM, so fidelity is more.
- Mainly used for steno transmission
