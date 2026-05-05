PsychophysicalMaster should run on a RPI connected to a network that is accessible by the RPIs running RunMatrix and the laptop running PsychophysicalInterface. The master will receive the experimental json from PsychophysicalInterface and execute the experiment.

config.json sets various parameters. The RPI this is run on needs to be able to accept connections over the network from all clients. 

A breadboard needs to connect:

Common grounds for all RPIs

The audio outputs (AUDIO_PORTS) to an amplifier

The TRIAL_RESET_PORT and TRIAL_START_PORT on the master to all slaves running RunMatrix, controlling the LEDmatrix


On each trial, it will:

Load experiment information from the network (PsychophysicalInterface) if USE_INTERFACE_NOT_FILE is set in config.json

Send a signal (TRIAL_RESET_PORT) that the trial is resetting

Inform (via network) the "slave" RPIs running RunMatrix as to visual information

Confirm that the slave RPIs have connected

Send a signal (TRIAL_START_PORT) triggering the trial start

During the trial, it will trigger GPIOs to play audio signals (claims the ports in AUDIO_PORTS, plays based on the experiment JSON). These ports need to be routed through a simple amp.
It will also record keypresses as a simple response measure.

inform and distribute pixel information to the RunMatrix RPIs, control the auditory output. It is also set to record keypresses as a response measure and record timestamps.

Uses the lgpio library to control the GPIOs.



A few other notes:

Make sure the RPIs have sufficient amps from the power supplies.

Auditory functionality is very limited -- think about what you really want prior to the experiment.

The networking code here is very simple, an asynchronous method may be preferable.

I was using a confirmatory signal from the slaves to the master via SLAVE_IMAGE_READY_PORTS, but in testing this doesn't seem to be required, so I dropped it.
