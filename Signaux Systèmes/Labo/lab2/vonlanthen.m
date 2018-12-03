%Labo 1 - Signaux & Syst�mes
%3.1 Signal entr� point � point
%D�claration des variables
t = (-2:1e-6:9);
f = 1000;
tau = 1e-3;
u=heaviside(t);

%Affichage fonction x1(t)
x1 = cos(2*pi*f * t);
subplot(3, 1, 1);
x = linspace(-2, 9);
y = linspace(-1, 1);
plot(t*1e3, x1,'b','Linewidth',2);
grid on;
xlim([-2 9]);
ylim([-1 1]);
ylabel(['\fontsize{16}', 'x_{1}(t)']);

%Affichage fonction x2(t)
x2 = cos(2*pi*f*t).*u;
subplot(3, 1, 2);
plot(t*1e3, x2,'r','Linewidth',2);
xlim([-2 9]);
ylim([-1 1]);
ylabel(['\fontsize{16}', 'x_{2}(t)']);

%Affichage fonction x3(t)
x3 = exp(-t/tau).*cos(2*pi*f*t).*u;
subplot(3, 1, 3);
plot(t*1e3, x3,'black','Linewidth',2);
xlim([-2 9]);
ylim([-1 1]);
ylabel(['\fontsize{16}', 'x_{3}(t)']);
xlabel(['\fontsize{10}', 't[ms]']);

%%
%3.2 S�rie
%D�claration des variables
t = (-1:1e-6:1);
f = 2;

%Fonction x1(t)
x1 = sin(2*pi*f*t)+(1/3)*sin(2*pi*3*f*t)+(1/5)*sin(2*pi*5*f*t)+(1/7)*sin(2*pi*7*f*t);
plot(t, x1);
hold on;

%Fonction x2(t)
x2 = cos(2*pi*f*t)+(1/3^2)*cos(2*pi*3*f*t)+(1/5^2)*cos(2*pi*5*f*t)+(1/7^2)*cos(2*pi*7*f*t);
plot(t,x2);
hold on;
xlabel(['\fontsize{10}', 't[s]']);

%%
%3.3 Repr�sentation fr�quentielle

%D�claration des variables
t = (-1:10e-6:1);
f = 2;
fe = 1/10e-6;
N = length(t);

%Calcul de l'abcisse
ab = (-1/2*fe+fe/N:fe/N:1/2*fe)-1/2*fe/N;

%Fonction x1(t)
x1=sin(2*pi*f*t)+1/3*sin(2*pi*3*f*t)+1/5*sin(2*pi*5*f*t)+1/7*sin(2*pi*7*f*t)+1/9*sin(2*pi*9*f*t);
a=fftshift(1/N*fft(x1));
subplot(4, 1, 1);
plot(ab, abs(a), 'black');
xlim([-20 20]);
ylim([-0.1 0.6]);
ylabel(['\fontsize{10}', 'Module Amplitude (x1)']);

subplot(4, 1, 2)
plot(ab, angle(a));
xlim([-20 20]);
ylim([-2 2]);
ylabel(['\fontsize{10}', 'Phase [rad]']);

%Fonction x2(t)
x2=cos(2*pi*f*t)+1/3^2*cos(2*pi*3*f*t)+1/5^2*cos(2*pi*5*f*t)+1/7^2*cos(2*pi*7*f*t)+1/9^2*cos(2*pi*9*f*t);
b=fftshift(1/N*fft(x2));
subplot(4, 1, 3);
plot(ab, abs(b), 'r');
xlim([-20 20]);
ylim([-0.1 0.6]);
ylabel(['\fontsize{10}', 'Module Amplitude (x2)']);

subplot(4, 1, 4);
plot(ab, angle(a));
xlim([-20 20]);
ylim([-2 1]);
xlabel(['\fontsize{10}', 'f[Hz]']);
ylabel(['\fontsize{10}', 'Phase [rad]']);

%%
%3.4 Analyse fr�quentielle

guitare = load('guitare.mat');
piano = load('piano.mat');

sound(guitare.music, guitare.Fs); %correspond � un LA (440 Hz)
sound(piano.music, piano.Fs); %correspond � un LA (440 Hz)

%%
%3.5 Optionnel (Partie 1)

%D�claration des variables
t = (-1:1e-5:1);

%Fonction Fourier(n)
subplot(2, 1, 1);
plot(t, Fourier(250),'red');
grid on;
ylabel(['\fontsize{16}', 'Fourier(n)']);

%Fonction Fourier2(n)
subplot(2, 1, 2);
plot(t, Fourier2(250),'black');
grid on;
xlabel(['\fontsize{10}', 't[s]']);
ylabel(['\fontsize{16}', 'Fourier2(n)']);
