filefid_1 = fopen('BuildInputFile.txt','r');
filefid_2 = fopen('tmp.txt','w');

control_num  = 0;

while(~feof(filefid_1))
    str = fgetl(filefid_1);
    
    if(strcmp(str,'*Point') == 1)
        control_num = 1;
        counter = 1;
        fprintf(filefid_2,'%s\n',str);
        str = fgetl(filefid_1);
        
    elseif(strcmp(str,'*Element') == 1)
        control_num = 2;
        counter = 1;
    else
%         control_num²»±ä»¯
    end
    
    
    if ((strcmp(str,'*Point')) == 1 || (strcmp(str,'*Element') == 1))
        fprintf(filefid_2,'%s\n',str);
    else
        switch (control_num) 
        case 0
            fprintf(filefid_2,'%s\n',str);
        case 1
            % *Point
            fprintf(filefid_2,'%s\n',[num2str(counter),',',str]);
            counter =counter + 1;
        case 2
            % *Element
            fprintf(filefid_2,'%s\n',[num2str(counter),',','QUAD4',',',str,',',num2str(1)]);
            counter =counter + 1;
        end
    end
end

fprintf(filefid_2,'*Material\n');
fprintf(filefid_2,'1,Linear,Iso,E,50000,Nu,0.3,RHO,1.0\n');
fprintf(filefid_2,'*EleProp\n');
fprintf(filefid_2,'1,Beam,Area,2.9,I1,3.5,I2,5.79\n');

fclose(filefid_1);
fclose(filefid_2);