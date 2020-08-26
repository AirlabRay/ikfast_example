#include <stdio.h>
#include <stdlib.h>

double* ik_euler(double* points,int i)
{
    IkSolutionList<IkReal> solutions;
    std::vector<IkReal> vfree(GetNumFreeParameters());
    IkReal eerot[9] = {0,};
    IkReal eetrans[3] = {0,};
    float rad = 180/3.14159;
    
    //Euler angle
    eetrans[0] = points[0];
    eetrans[1] = points[1];
    eetrans[2] = points[2];
    IkReal Rx = points[3]/rad;
    IkReal Ry = points[4]/rad;
    IkReal Rz = points[5]/rad;
    
    eerot[0] = IKcos(Rz)*IKcos(Ry);
    eerot[1] = IKcos(Rz)*IKsin(Ry)*IKsin(Rx) - IKsin(Rz)*IKcos(Rx);
    eerot[2] = IKcos(Rz)*IKsin(Ry)*IKcos(Rx) + IKsin(Rz)*IKsin(Rx);
    eerot[3] = IKsin(Rz)*IKcos(Ry);
    eerot[4] = IKsin(Rz)*IKsin(Ry)*IKsin(Rx) + IKcos(Rz)*IKcos(Rx);
    eerot[5] = IKsin(Rz)*IKsin(Ry)*IKcos(Rx) - IKcos(Rz)*IKsin(Rx);
    eerot[6] = -1*IKsin(Ry);
    eerot[7] = IKcos(Ry)*IKsin(Rx);
    eerot[8] = IKcos(Ry)*IKcos(Rx);

    bool bSuccess = ComputeIk(eetrans, eerot, 0, solutions);
    if( !bSuccess ) {
        fprintf(stderr,"Failed to get ik solution\n");
    }

    static double solvalues[6]={0,};
    const IkSolutionBase<IkReal>& sol = solutions.GetSolution(i);
    sol.GetSolution(&solvalues[0],0);
    for(int j = 0; j < 6; j++)
    {
	solvalues[j] = solvalues[j]*rad;
    }
    return solvalues;
}

double* fk_euler(double* joints)
{
    IkReal eetrans[3] = {0,};
    IkReal eerot[9] = {0,};
    IkReal j[6] = {0,};
    IkReal Rx = 0,Ry = 0,Rz = 0;
    float rad = 180/3.14159;
    static double solutions[6]={0,};
    for(int i=0;i<6;i++)
    	joints[i]=joints[i]/rad;	

    ComputeFk(j, eetrans, eerot); //input:j1~j6 output:trans and rot matrix

    //Euler inverse
    Ry = IKasin(-1*eerot[6]);
    Rx = IKatan2(eerot[7]/IKcos(Ry),eerot[8]/IKcos(Ry));
    Rz = IKatan2(eerot[3]/IKcos(Ry),eerot[0]/IKcos(Ry));
    
    solutions[0] = eetrans[0];
    solutions[1] = eetrans[1];
    solutions[2] = eetrans[2];
    solutions[3] = Rx * rad;
    solutions[4] = Ry * rad;
    solutions[5] = Rz * rad;
    return solutions;
}