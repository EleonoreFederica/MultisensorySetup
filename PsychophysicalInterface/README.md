This program is run on a laptop that connects to a controller running PsychophysicalMaster.

The application provides a GUI for configuring and uploading experiments to PsychophysicalMaster. Each experiment that is configured is transmitted in JSON format. The GUI allows you to set experimental parameters (e.g., subject name), add Visual and Auditory trials, edit or delete created trials, or "mix" (combine) created trials into a new trial that contains the stimuli of the mixed/combined trials (useful for creating visual-auditory, visual-visual, and auditory-auditory trials). Note that mixing creates a new trial, it does not create pointers to the existing trial, so modifications on the mixed trial are not backpropogated.

The GUI has a field for the IP address of the CPU (i.e., a RPI) running PsychoPhysicalMaster, no other configuration is necessary. It connects via Port 13 using simple code (that could be improved).
