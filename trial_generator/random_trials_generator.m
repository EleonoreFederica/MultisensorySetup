 % RANDOM TRIAL GENERATOR
% a code to generate a serie of AV trials in a random way: fix the total #
% of trials, the onset and offset stimuli parameters, the images to be
% displayed on the matrices and audio parametrs. The code will randomly set for each trial: the
% duration of ITI between 1000 and 1500 ms, the tuype of trial (A/V/AV),
% the audio channel and the follower device target for the visual stimuli

clc, clear all, close all

N_trials = 100; %number of trials in the train
trial_type= ["A", "V", "AV"];
target_slaves = ["SLAVE1", "SLAVE2"];
audio_channels = [6, 7]; % audio GPIO ports: 6 -> RIGHT // 7 -> LEFT
onset = 0; %ms
offset = 50; %ms
%% inter trial intervals
rand_values = 1000:1500;
iti_val = rand_values(randi(length(rand_values),1,N_trials)); % set of 100 random falues of Inter-Trrial Intervals between 1500ms and 1500ms

%% video stimuli parameters
% images managment
image_files= {"visual cues led matrices\left_matrix.png", "visual cues led matrices\right_matrix.png"};
l = length(image_files);
w = 128;
h = 64;
c = 3;
image = zeros(h,w,c,'uint8');
pixels1 = [];
pixels2 = [];
for i=1:l
    image(:,:,:,i) = imread(image_files{i});
end

% conversion into pixels array [x,y,R,G,B]
% pixel arrays for image 1
for x = 1:h
    for y = 1:w
        R = image(x, y, 1, 1);
        G = image(x, y, 2, 1);
        B = image(x, y, 3, 1);
        
        %check if the xy pxl is NOT black
        if ~(R == 0 && G == 0 && B == 0)
            pixels1 = [pixels1; x-1, y-1, R, G, B]; % append pixel
        end
    end
end

% pixel arrays for image 1
for x = 1:h
    for y = 1:w
        R = image(x, y, 1, 2);
        G = image(x, y, 2, 2);
        B = image(x, y, 3, 2);
        
        %check if the xy pxl is NOT black
        if ~(R == 0 && G == 0 && B == 0)
            pixels2 = [pixels2; x-1, y-1, R, G, B]; % append pixel
        end
    end
end
Pixel = {pixels1, pixels2}; % cell containing all the loaded images in json format as array of pixels information: [x, y, r, g, b]
%% acoustic stimuli parameters
freq = 5000; %Hz
d_c = 50; %perc
cycle_offset = 0;

%% JSON structures creation
% building of a series of JSON files (in total = # trials -> N_trial) in
% random way: random definition of type (A,V,AV), random trial duration by
% the iti_val vectors, random selection of the target for visual stumili

for i = 1:N_trials
    trial_duration = offset + iti_val(i); % durationof the i-th trial
    idxTrialTypeRand = randi(length(trial_type));
    type = trial_type(idxTrialTypeRand);
    idxAudioChanRand = randi(length(audio_channels));
    idxContrTargetRand = randi(length(target_slaves));
    idxPixelRand = randi(length(Pixel));
    trial = struct; % define each trial as a structure of sub-fields to acilitate the conversion into json format
    trial.DURATION = trial_duration;
    trial.AUDITORY_STIMULI = [];
    trial.VISUAL_STIMULI = [];
    switch type
        case "A"
            trial.TRIAL_TYPE = "A";
            if idxAudioChanRand == 1
                trial.NAME  = sprintf("trial_A_%s_%d", "right", trial_duration);
            else
                trial.NAME  = sprintf("trial_A_%s_%d", "left", trial_duration);
            end
            auditoryStimuli = struct;
            auditoryStimuli.CHANNEL = audio_channels(idxAudioChanRand);
            auditoryStimuli.ONSET = onset;
            auditoryStimuli.OFFSET = offset;
            auditoryStimuli.FREQUENCY = freq;
            auditoryStimuli.DUTY_CYCLE = double(d_c);
            auditoryStimuli.CYCLE_OFFSET = cycle_offset;
    
            trial.AUDITORY_STIMULI = {auditoryStimuli};
            trial.VISUAL_STIMULI = [];
        case "V"
            trial.TRIAL_TYPE = "V";
            trial.NAME  = sprintf("trial_V_%s_%d", target_slaves(idxContrTargetRand), trial_duration);
            visualStimuli = struct;
            visualStimuli.CONTROLLER_TARGET = target_slaves(idxContrTargetRand);
            visualStimuli.ONSET = onset;
            visualStimuli.OFFSET = offset;
            visualStimuli.PIXELS = Pixel{idxPixelRand};
            
            trial.VISUAL_STIMULI = {visualStimuli};
            trial.AUDITORY_STIMULI = [];
        case "AV"
            trial.TRIAL_TYPE = "AV";
            if idxAudioChanRand == 1
                trial.NAME  = sprintf("trial_AV_%s%s_%d", target_slaves(idxContrTargetRand), "right", trial_duration);
            else
                trial.NAME  = sprintf("trial_AV_%s%s_%d", target_slaves(idxContrTargetRand), "left", trial_duration);
            end
            auditoryStimuli = struct;
            auditoryStimuli.CHANNEL = audio_channels(idxAudioChanRand);
            auditoryStimuli.ONSET = onset;
            auditoryStimuli.OFFSET = offset;
            auditoryStimuli.FREQUENCY = freq;
            auditoryStimuli.DUTY_CYCLE = double(d_c);
            auditoryStimuli.CYCLE_OFFSET = cycle_offset;
            visualStimuli = struct;
            visualStimuli.CONTROLLER_TARGET = target_slaves(idxContrTargetRand);
            visualStimuli.ONSET = onset;
            visualStimuli.OFFSET = offset;
            visualStimuli.PIXELS = Pixel{idxPixelRand};
            trial.AUDITORY_STIMULI = {auditoryStimuli};
            trial.VISUAL_STIMULI = {visualStimuli};
        otherwise
    end
    % convert the structure into a json format
    jsonStr = jsonencode(trial);
    
    % decide the saving path for the file
    savePath = fullfile(getenv('USERPROFILE'), 'Desktop', 'tesi magistrale', 'Codici', 'PsychophysicalInterface-master', 'testing_trials');
    if ~exist(savePath, 'dir')
        mkdir(savePath);
    end

    % Save each json file into a specific path
    fileName = fullfile(savePath, sprintf('%s.json', trial.NAME));
    fid = fopen(fileName, 'w', 'n', 'UTF-8');
    if fid == -1
        error('Impossibile aprire il file per la scrittura');
    end
    fwrite(fid, jsonStr, 'char');
    fclose(fid);   
end
