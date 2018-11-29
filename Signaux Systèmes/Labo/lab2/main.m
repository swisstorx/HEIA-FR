clear;close all;
uin=[500 496 496 496 496 496 496 496 496 496 492 492 492 488];
uout=[488 356 248 192 152 128 112 96 88 80 72 68 60 48];
f=[1 4 7 10 13 16 19 22 25 28 31 34 37 40];
plot(f,uout./uin,"Blue");
xlabel(['Fréquence kHz']);
ylabel(['Rapport Uout/Uin']);
xlim([1 40]);
ylim([0 1]);
grid on;

% semilogx(f,20*log10(uout./uin))



