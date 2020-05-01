function [ result ] = milp( L )
%L���ķ���������·�����ĵ�ľ��롣����Χ��[20,500]U{0}��0ֵ�ڱ������л�Ԥ����Ϊ500��
%A���ķ�����������
%W���ķ�����������
%·����N=8����ͻ����P=16
tic
C1 = 2;
M = 50000;
%safe_coef = 2;
A = 4;
W = 2;
Le = 0.5 * (A + W);
Ls = 1 * (A + W);

%% ·����ز���
lanewid = 4;%������
lanenum = 3;%������
radius = 4;%��ת������Ե�뾶

R = radius + (lanenum+0.5) * lanewid;%18,��ת�뾶
stop_dis = radius + lanenum * lanewid;%16
const1 = radius + (1+0.5) * lanewid;%10,ֱ�г������Ҳ�ת�����ĵľ���
const2 = stop_dis;%16,��ת����㵽ת�����ĵľ���
%% 
for i = 1 : length(L)
    if L(i) == 0 %���������������control_scopeС�ܶ��ֵ���˴�Ψһ������ĳ����������������ֶ�̬�����ų����⡣��Ҫ������0����500
        L(i) = max(L)+150;%500�����ã�Զ�������೵�����루һ����control_scopeȡֵ��������ͬʱ�ֱ����M����һ���������������M��ʧЧ
    end
end

L1 = L(1); L2 = L(2); L3 = L(3); L4 = L(4); L5 = L(5); L6 = L(6); L7 = L(7); L8 = L(8);
L1_18 = L1 - stop_dis + R * asin(  const1/R  );%��СԲ��
L1_17 = L1 - stop_dis + R * asin(  const2/R  );%��Բ��
L1_16 = L1 - stop_dis + R * acos(  const1/R  );%�д�Բ��
L1_13 = L1 - stop_dis + pi/2*R - R * asin(  const2/R  );%СԲ��

L2_28 = L2 - stop_dis + const1;%��
L2_25 = L2 - stop_dis + (2*stop_dis - sqrt(R^2 - const1^2));%�г�
L2_24 = L2 - stop_dis + 2 * stop_dis - const1;%��
L2_23 = L2 - stop_dis + sqrt(R^2 - const1^2);%�ж�

L3_13 = L3 - stop_dis + R * asin(  const2/R  );%��Բ��
L3_23 = L3 - stop_dis + R * asin(  const1/R  );%��СԲ��
L3_38 = L3 - stop_dis + R * acos(  const1/R  );%�д�Բ��
L3_35 = L3 - stop_dis + pi/2*R - R * asin(  const2/R  );%СԲ��

L4_24 = L4 - stop_dis + const1;%��
L4_47 = L4 - stop_dis + (2*stop_dis - sqrt(R^2 - const1^2));%�г�
L4_46 = L4 - stop_dis + 2 * stop_dis - const1;%��
L4_45 = L4 - stop_dis + sqrt(R^2 - const1^2);%�ж�

L5_25 = L5 - stop_dis + R * acos(  const1/R  );%�д�Բ��
L5_35 = L5 - stop_dis + R * asin(  const2/R  );%��Բ��
L5_45 = L5 - stop_dis + R * asin(  const1/R  );%��СԲ��
L5_57 = L5 - stop_dis + pi/2*R - R * asin(  const2/R  );%СԲ��

L6_16 = L6 - stop_dis + (2*stop_dis - sqrt(R^2 - const1^2));
L6_46 = L6 - stop_dis + const1;%��
L6_67 = L6 - stop_dis + sqrt(R^2 - const1^2);%�ж�
L6_68 = L6 - stop_dis + 2 * stop_dis - const1;%��

L7_17 = L7 - stop_dis + pi/2*R - R * asin(  const2/R  );%СԲ��
L7_47 = L7 - stop_dis + R * acos(  const1/R  );%�д�Բ��
L7_57 = L7 - stop_dis + R * asin(  const2/R  );%��Բ��
L7_67 = L7 - stop_dis + R * asin(  const1/R  );%��СԲ��

L8_18 = L8 - stop_dis + sqrt(R^2 - const1^2);
L8_28 = L8 - stop_dis + 2 * stop_dis - const1;
L8_38 = L8 - stop_dis + (2*stop_dis - sqrt(R^2 - const1^2));%�г�
L8_68 = L8 - stop_dis + const1;%��


f = [-1;-1;-1;-1;-1;-1;-1;-1; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0];
      %V1               V2               V3               V4              V5               V6               V7               V8        B18   B17   B16   B13   B28   B25   B24   B23   B38   B35    B47   B46   B45    B57   B67    B68 
A=[   
    Le - L8_18          0                0                0               0                0                0           Ls + L1_18     M     0     0     0     0     0     0     0     0     0      0     0     0      0     0      0;
    Ls + L8_18          0                0                0               0                0                0           Le - L1_18    -M     0     0     0     0     0     0     0     0     0      0     0     0      0     0      0;% veh1 - veh8 conflict
       
    Le - L7_17          0                0                0               0                0            Ls + L1_17           0         0     M     0     0     0     0     0     0     0     0      0     0     0      0     0      0;
    Ls + L7_17          0                0                0               0                0            Le - L1_17           0         0    -M     0     0     0     0     0     0     0     0      0     0     0      0     0      0;% veh1 - veh7 conflict
          
    Le - L6_16          0                0                0               0            Ls + L1_16           0                0         0     0     M     0     0     0     0     0     0     0      0     0     0      0     0      0;
    Ls + L6_16          0                0                0               0            Le - L1_16           0                0         0     0    -M     0     0     0     0     0     0     0      0     0     0      0     0      0;% veh1 - veh6 conflict
          
    Le - L3_13          0           Ls + L1_13            0               0                0                0                0         0     0     0     M     0     0     0     0     0     0      0     0     0      0     0      0;
    Ls + L3_13          0           Le - L1_13            0               0                0                0                0         0     0     0    -M     0     0     0     0     0     0      0     0     0      0     0      0;% veh1 - veh3 conflict
    
    
    
       0           Le - L8_28            0                0               0                0                0           Ls + L2_28     0     0     0     0     M     0     0     0     0     0      0     0     0      0     0      0;
       0           Ls + L8_28            0                0               0                0                0           Le - L2_28     0     0     0     0    -M     0     0     0     0     0      0     0     0      0     0      0;% veh2 - veh8 conflict
       
       0           Le - L5_25            0                0           Ls + L2_25           0                0                0         0     0     0     0     0     M     0     0     0     0      0     0     0      0     0      0;
       0           Ls + L5_25            0                0           Le - L2_25           0                0                0         0     0     0     0     0    -M     0     0     0     0      0     0     0      0     0      0;% veh2 - veh5 conflict
          
       0           Le - L4_24            0           Ls + L2_24           0                0                0                0         0     0     0     0     0     0     M     0     0     0      0     0     0      0     0      0;
       0           Ls + L4_24            0           Le - L2_24           0                0                0                0         0     0     0     0     0     0    -M     0     0     0      0     0     0      0     0      0;% veh2 - veh4 conflict
          
       0           Le - L3_23        Ls + L2_23           0               0                0                0                0         0     0     0     0     0     0     0     M     0     0      0     0     0      0     0      0;
       0           Ls + L3_23        Le - L2_23           0               0                0                0                0         0     0     0     0     0     0     0    -M     0     0      0     0     0      0     0      0;% veh2 - veh3 conflict
    
    
     
       
       0                0            Le - L8_38           0               0                0                0           Ls + L3_38     0     0     0     0     0     0     0     0     M     0      0     0     0      0     0      0;
       0                0            Ls + L8_38           0               0                0                0           Le - L3_38     0     0     0     0     0     0     0     0    -M     0      0     0     0      0     0      0;% veh3 - veh8 conflict
       
       0                0            Le - L5_35           0          Ls + L3_35            0                0                0         0     0     0     0     0     0     0     0     0     M      0     0     0      0     0      0;
       0                0            Ls + L5_35           0          Le - L3_35            0                0                0         0     0     0     0     0     0     0     0     0    -M      0     0     0      0     0      0;% veh3 - veh5 conflict
          
       0                0                0            Le - L7_47          0                0            Ls + L4_47           0         0     0     0     0     0     0     0     0     0     0      M     0     0      0     0      0;
       0                0                0            Ls + L7_47          0                0            Le - L4_47           0         0     0     0     0     0     0     0     0     0     0     -M     0     0      0     0      0;% veh4 - veh7 conflict
          
       0                0                0            Le - L6_46          0           Ls + L4_46            0                0         0     0     0     0     0     0     0     0     0     0      0     M     0      0     0      0;
       0                0                0            Ls + L6_46          0           Le - L4_46            0                0         0     0     0     0     0     0     0     0     0     0      0    -M     0      0     0      0;% veh4 - veh6 conflict
       
       
       
       
       0                0                0            Le - L5_45     Ls + L4_45            0                0                0         0     0     0     0     0     0     0     0     0     0      0     0     M      0     0      0;
       0                0                0            Ls + L5_45     Le - L4_45            0                0                0         0     0     0     0     0     0     0     0     0     0      0     0    -M      0     0      0;% veh4 - veh5 conflict
       
       0                0                0                0          Le - L7_57            0            Ls + L5_57           0         0     0     0     0     0     0     0     0     0     0      0     0     0      M     0      0;
       0                0                0                0          Ls + L7_57            0            Le - L5_57           0         0     0     0     0     0     0     0     0     0     0      0     0     0     -M     0      0;% veh5 - veh7 conflict
          
       0                0                0                0               0           Le - L7_67        Ls + L6_67           0         0     0     0     0     0     0     0     0     0     0      0     0     0      0     M      0;
       0                0                0                0               0           Ls + L7_67        Le - L6_67           0         0     0     0     0     0     0     0     0     0     0      0     0     0      0    -M      0;% veh6 - veh7 conflict
          
       0                0                0                0               0           Le - L8_68            0            Ls + L6_68    0     0     0     0     0     0     0     0     0     0      0     0     0      0     0      M;
       0                0                0                0               0           Ls + L8_68            0            Le - L6_68    0     0     0     0     0     0     0     0     0     0      0     0     0      0     0     -M;% veh6 - veh8 conflict
       
    ];
b  = [M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0;  M;  0; M;  0;  M;  0;  M;  0;  M;  0];
lb = [10; 10; 10; 10;  10; 10; 10; 10;       0;  0;  0;  0;  0;  0;  0;  0;  0;  0;  0;  0;  0;  0;  0;  0];
ub = [20; 20; 20; 20;  20; 20; 20; 20;       1;  1;  1;  1;  1;  1;  1;  1;  1;  1;  1;  1;  1;  1;  1;  1];

options = optimoptions('intlinprog','Display','off');
%result = intlinprog(f, [9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24], A, b, [], [], lb, ub,[]);%,options);
result = intlinprog(f, [9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24], A, b, [], [], lb, ub,[],options);
%�ų���ֵ���ȴ�����Ӱ��

for i = 1:8
    if abs(result(i)-20) < 0.01
        result(i) = 20;
    end
end
for i = 9:24
    if abs(result(i)-1) < 0.01
        result(i) = 1;
    end
end
toc
end