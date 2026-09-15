#include <iostream>
#include <fstream>
#include <cmath>

//发动机参数，可修改
int main()
{
    double compression_ratio = 16.0;   //压缩比，可以修改
    int rpm = 2000;                   //转速
    double injection_advance = 15.0;  //喷油提前角 度CA

    std::ofstream outfile("sim_result.csv");
    outfile << "crank_angle,volume,pressure,temperature\n";

    double gamma = 1.35;
    double Vc = 0.00002;
    double Vh = Vc * (compression_ratio - 1.0);

    for (double ca = -180;ca <= 180;ca += 1.0)
    {
        double theta = ca * 3.1415926 / 180.0;
        double volume = Vc + Vh / 2.0 * (1 - cos(theta));

        //简单绝热压缩膨胀
        double vol_ratio = volume / (Vc);
        double press = 101325 * pow(vol_ratio, gamma);
        double temp = 300 * pow(vol_ratio, gamma - 1);

        outfile << ca << "," << volume << "," << press << "," << temp << "\n";
    }
    outfile.close();
    std::cout << "仿真完成，输出sim_result.csv，可以用Excel打开绘图\n";
    return 0;
}