%point 3.1
clear; close all;
tFin=10;
fe=44.1e3;
b = [0.3 0.36 0.36 0.3];
t = (0:1/fe:tFin);
f0=0;



%sound(res);

load('music.mat');
% sound(music,Fs);
y=filter_no_recursive(music,b);
% sound(y,fe);
figure;
plot(t,y);

x= filter_no_recursive(chirp(t,f0,tFin,fe/2),b);
res = filter_no_recursive(x,b);
figure;
plot(t,x);


figure;
xx = chirp(t,0,10,20000);
yy = filter_no_recursive(xx, b);
figure;
plot(t,yy);


% Réponse en fréquence3.3
figure('name','Filtre non récursif');
H_no_rec = tf(b,[1 0 0 0],(1/fe));
bode(H_no_rec)
grid on

%%
%point 3.2

clear; close all;
f0=0;
tFin=10;
fe=44.1e3;
a = [1 -1.8 0.8];
b = [1.6 -3.2 1.6];
t = (0:1/fe:tFin);
load('music.mat');
y=filter_recursive(music,a,b);

%sound(y,fe);
plot(t,y);

% Réponse en fréquence 3.3
figure('name','filtre recursif');
H_no_rec = tf(b,a,(1/fe));
bode(H_no_rec)
grid on












































