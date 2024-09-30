#pragma once
#include <math.h>
#include <fstream>
#include <sstream>
#include "process.h"


class Integral : public Process
{
    private:
        int intervals = 10;
        double xl = -0.2, xh = 1.0, c = 0.9, 
            h, sum = 0.0, startwtime, endwtime;
        
        std::ofstream fout;

    public:
        Integral(int argc, char* argv[], MPI_Comm comm = MPI_COMM_WORLD, std::string filename = "file.txt") : Process(argc, argv, comm)
        {
            fflush(NULL);
            fout.open(filename, std::ios::out);
            fflush(NULL);
        }
        ~Integral() { 
            fout.close(); 
        }

        int get_intervals() {

            if (process_ID == Process::INIT) {
                std::cout << "Введите кол-во интервалов: ";
                std::cin >> intervals;
            }

            return intervals;
        }

        double calculate_integral() {
            h = (xh - xl) / static_cast<double>(intervals);
            
            std::cout << h;
            for (int i = process_ID + 1; i <= intervals; i += numprocs) {
                double x = xl + h * ((double)i - 0.5);
                sum += f(x, c);
            }

            sum *= h;

            std::stringstream str;
            str << std::scientific << "Сумма: " << sum;
            Process::printInfo(str.str());
            fflush(NULL);
            str.clear();
            str.str("");

            return sum;
        }

        double sum_results_process() {
            double integral = 0;
            reduce(&sum, &integral, MPI_DOUBLE);
            endwtime = MPI_Wtime();

            if (process_ID == Process::INIT) {
                Init_Process::printInfo("", fout);
                printInfo("", fout);
                std::stringstream str;
                str << std::scientific << "Апроксимация интегралла: " << integral;
                Process::printInfo(str.str(), fout);
                fflush(NULL);
                str.clear();
                str.str("");
                str << std::scientific << "Ошибка: " << integral - fi(xh, c) + fi(xl, c);
                Process::printInfo(str.str(), fout);
                fflush(NULL);
                str.clear();
                str.str("");
                str << std::scientific << "Время подсчета: " << endwtime - startwtime;
                Process::printInfo(str.str(), fout);
                fflush(NULL);
                str.clear();
                str.str("");
                return integral;
            }

            return sum;
        }

        static double f(double a, double c) {
            return 1 / (1 + pow(c * a, 2));
        }

        static double fi(double a, double c) {
            return (1 / c) * atan(c * a);
        }

        friend std::ostream& operator<<(std::ostream& out, Integral& integral) {
            return out << "\n\nКол-во интервалов: " << integral.intervals << 
                "\nНижняя граница: " << integral.xl << "\nВерхняя граница: " << integral.xh << 
                "\nПараметр с: " << integral.c << "\n\nСумма интеграла: " << integral.sum << std::endl;
        }
};