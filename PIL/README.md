# Processor In Loop Simulation

When developing embedded control algorithms engineers often wish to test their code by executing it inside a circuit simulator. With the MATLAB PIL package, this can be done by tying actual code executing on real hardware into the virtual world of a MATLAB model.

Instead of reading the physical sensors, values calculated by the simulation tool are used as inputs to the embedded algorithm. Similarly, outputs of the control algorithms executing on the processor are fed back into the simulation to drive the virtual environment. 

This approach can expose platform-specific software defects such as overflow conditions and casting errors. PIL simulations can also detect and analyze potential problems related to the multi-threaded execution of control algorithms, including jitter and resource corruption.

A specialized PIL Block serves as the interface between simulation model and embedded processor.

Having gone through the basic idea of what is PIL, let's get more specific on the implementation of PIL in MATLAB. 

We test numerical equivalence between model components and production code that you generate from the components by using software-in-the-loop (SIL) and processor-in-the-loop (PIL) simulations.
With a SIL simulation, you test source code on your development computer.
</br>
With a PIL simulation, you test the **compiled object** code that you intend to deploy in production by running the object code on real target hardware or an instruction set simulator. 
</br>
To determine whether model components and generated code are numerically equivalent, compare SIL and PIL results against normal mode results.

There are three ways of running SIL and PIL simulations. You can use the top model, Model blocks, or SIL and PIL blocks that you create from a subsystem.



## Target Connectivity Configuration for PIL
Before you can run PIL simulations, you must configure target connectivity. The target connectivity configuration enables the PIL simulation to:

- Build the target application.
- Download, start, and stop the application on the target.
- Support communication between Simulink and the target.