% Interface Programm for Remote Node: Displays all data in a nice chart, m8
check = 0;
tx_data = "10,20,30,40";
checkstr = "Init finished";
comparestr = "init not fin";
sample_num= 50; 
x=1:sample_num;
ys=  zeros(4,length(x));

% Temperature /°C, Distance / cm, U1/V U2/V
multiplicators = [1,1,5/1024,5/1024];

% Connect to Device
dut = serialport('COM5',9600);
configureTerminator(dut,"LF");
% check if connection is established
comparestr = read(dut,13,'string');
check = strcmp(checkstr,comparestr);
%%
sample = 0;
colorcodec =["rx","mx","bx","kx"];

% Read data
if(check)
    for sample=1:1:sample_num
        
        tx_data = readline(dut);
        % seperate string at ","
        split = strsplit(tx_data,',');
        data = str2double(split);

        for z=1:1:4
        ys(z,sample)=data(z);
        end
        
        % Temperaturedate needs some filtering
        subplot(3,1,1);
        plot(x(1:sample),ys(1,1:sample),'b-')
        ylim([0 50])
        hold on;
        
        subplot(3,1,2);
        plot(x(1:sample),ys(2,1:sample),'b-')
        ylim([0 50])
        hold on;
        
        subplot(3,1,3);
        plot(x(1:sample),ys(3,1:sample),'b-')
        drawnow limitrate;
        ylim([0 1024])
        hold on;
    end
else
    disp("----Check Setup! Device Initialization failed!---")
end
delete(dut);