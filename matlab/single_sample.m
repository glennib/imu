%clear all;
close all;

PATH = '../samples/';
FILE_NAME = 'itg_2016-02-01_100Hz_60s.ods';

FREQUENCY = 100; % Hz

complete_path = strcat(PATH, FILE_NAME);
sample = xlsread(complete_path);

n = size(sample, 1);

nu = mean(sample);

sigma_2 = var(sample);

sigma = sqrt(sigma_2);

figure;
plot(1:n, sample-nu)

figure;
autocorr(sample-nu)

