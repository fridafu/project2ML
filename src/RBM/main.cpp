#include <iostream>
#include "solver.h"
#include "bruteforce.h"
#include "impsamp.h"
#include "gibbs.h"
#include <limits>
using namespace std;
using namespace arma;

int main(){
    double rho = 0.4;
    int numpart = 1;
    int mc = 500000;//(1048576 + 1000) / numpart; // Monte Carlo Cycles
    int howmanyDs = 1;
    double omega = 1;
    double sig = 1;
    int hidden = 2;
//    double dt = 0.01;
    double gamma = 0.01;
    int gdc = 1000; // Gradient Decent Cycles
    bool interactionswitch = false;
    double spread = 0.3;
//    vec dtvec = {0.001,0.01,0.1,0.2,0.5,0.8};
//    vec dtvec = {0.8,0.85,0.9,0.95,1.0,1.05,2};
//    vec dtvec = {1.05,1.1,1.15,1.20,1.25,1.30,1.35,1.4,1.45,1.5,1.55,1.6};
    vec gammavec ={0.01,0.05,0.1,0.5,1.0};// {0.9, 1.0, 1.1, 1.25, 1.5, 1.75, 2.0};
//    vec gammavec = {2.5,3.0,3.5,4.0};
    //vec rhovec = {0.1,0.2,0.4,0.7,0.8,1.0};
    //vec dtvec = logspace<vec>(-4,0,51);
//    vec hvec = {0,1,2,3,4,5};
    double dt = 0.01;
    Solver S2(omega, rho, mc, numpart, howmanyDs, dt, sig, hidden, interactionswitch, spread); // initialize Solver class
    vec b = S2.init_b(spread); // depends on H
    mat w = S2.init_w(spread); // depens on H
    vec X = S2.init_X(); //GAUSSIAN IN IMPSAMP?
    vec a = S2.init_a(spread);
//    double dt = 1.1;
    for(int i=0;i<size(gammavec,0);i++){//size(dtvec,0)
//        double dt = dtvec(i);
//        hidden = hvec(i);
        //rho = rhovec(i);
        gamma = gammavec(i);
//        double gamma = gammavec(i);
        Solver S(omega, rho, mc, numpart, howmanyDs, dt, sig, hidden, interactionswitch, spread); // initialize Solver class
        string filename ="N" + std::to_string(numpart)+ "_d" + std::to_string(howmanyDs)+"gam" + std::to_string(gamma) + "_H" + std::to_string(hidden);

//        vec b = S.init_b(spread);
//        mat w = S.init_w(spread);
//        ofstream brutefile;
//        ofstream brutefile2;
//        brutefile.open("brute_" + filename + "_rho"+std::to_string(rho) +  ".dat");
        //brutefile2.open("brute_" + filename + "_energy.dat");
//        Bruteforce* B = new Bruteforce(omega, rho, mc, numpart, howmanyDs, dt, sig, hidden, interactionswitch, spread);
//        B->best_params(brutefile,brutefile2,gamma,a,b,w,X,gdc);
        //brutefile2.close();
//        brutefile.close();
        cout << a << endl;
        ofstream impfile;
        ofstream impfile2;
        impfile.open("imp_" + filename + "_dt"+std::to_string(dt) + ".dat");
        //impfile2.open("imp_" + filename + "_dt"+std::to_string(dt) + "_energy.dat");
        Impsamp* I = new Impsamp(omega, rho, mc, numpart, howmanyDs, dt, sig, hidden, interactionswitch, spread);
        I->best_params(impfile,impfile2,gamma,a,b,w,X,gdc);
        //impfile2.close();
        impfile.close();

//        ofstream gibfile;
//        ofstream gibfile2;
//        gibfile.open("gibbs_" + filename + "_sig"+std::to_string(sig) + ".dat");
        //gibfile2.open("gibbs_" + filename + "_energy.dat");
//        Gibbs* G = new Gibbs(omega, rho, mc, numpart, howmanyDs, dt, sig, hidden, interactionswitch, spread);
//        G->best_params(gibfile,gibfile2,gamma,a,b,w,gdc);
        //gibfile2.close();
//        gibfile.close();


//       B->solve(a, b, w, X, myfile, myfile2);

        //delete G;
        delete I;
//        delete B;
        // Illuminati!

        /*
        vec b = {0.000667904,0.00171753};
        mat w = {{0.00117447, 0.000381313},{-0.00166561, -0.000559385},{-0.000244628, -0.00130079}, {0.00103996, -0.00180347}};
        vec X = {1,2,3,4};
        vec X = {-0.436988, -0.243587,0.22773,0.146376};
        vec a ={0.000586069,0.000838821,0.000520396,0.000574091};
        */
    }



//    double exact_vint = 1./sqrt(2) + 1./sqrt(18)+1./sqrt(8);
//    vec Xtry = {0, 0, 1, 1, 3, 3, 7,7};
//    cout << scientific << exact_vint << endl;
//    cout << scientific << S.calc_interaction(Xtry) << endl;


    //}
    //}
    // thermalize the grad
    // vary spread
    // vary learning rate
    // vary hidden nodes, in non-interaction case H = 0 is best
    // interaction - 5 nodes?
}
