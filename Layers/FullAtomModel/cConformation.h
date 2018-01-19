#ifndef CCONFORMATION_H_
#define CCONFORMATION_H_
#include <cVector3.h>
#include <cMatrix44.h>
#include <vector>
#include <string>
#include <cRigidGroup.h>
#include <cGeometry.h>

class cTransform{
    public:
        double *alpha, *beta;
        double *grad_alpha;
        double d;
        
        cMatrix44 getRx(double angle);
        cMatrix44 getDRx(double angle);
        cMatrix44 getRy(double angle);
        cMatrix44 getRz(double angle);
        cMatrix44 getT(double dist, char axis);
    public:
        cMatrix44 mat, dmat;
        cTransform(double *param_alpha, double *param_beta, double d, double *grad_alpha){
            this->alpha = param_alpha;
            this->beta = param_beta;
            this->d = d;
            this->grad_alpha = grad_alpha;
        };
        ~cTransform(){};
        void updateMatrix();
        void updateDMatrix();
        void print();
};

class cNode{
    public:
        cRigidGroup *group;
        cTransform *T; //transform from parent to this node
        cMatrix44 M; //aggregate transform from root
        cMatrix44 F; //matrix for computing gradient
        cNode *left;
        cNode *right;
        cNode *parent;
                
        cNode(){parent = NULL;left=NULL;right=NULL;};
        ~cNode(){};
};

std::ostream& operator<<(std::ostream& os, const cNode& node);

class cConformation{
    // private:
    public:
        std::vector<cNode*> nodes;
        std::vector<cRigidGroup*> groups;
        std::vector<cTransform*> transforms;
        
        double zero_const, omega_const;
        double *atoms_global; //pointer to computed coordinates
        cGeometry geo;
        uint num_atoms;

    public:
        cNode *root;

        // Construct protein graph and bind grad to the angles
        cConformation(std::string aa, double *angles, double *angles_grad, uint angles_length, double *atoms_global);    
        ~cConformation();
        
        void print(cNode *node);

        // Backward propagation with external gradients
        double backward(cNode *root_node, cNode *node, double *atoms_grad);
        void backward(cNode *node, double *atoms_grad);

        //Computes coordinates of the atoms
        void update(cNode *node);

    private:
        cNode *addNode(cNode *parent, cRigidGroup *group, cTransform *t);
        
        cNode *addGly(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addAla(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addSer(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addCys(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addVal(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addIle(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addLeu(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addThr(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addArg(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addLys(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addAsp(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addAsn(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addGlu(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addGln(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addMet(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addHis(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addPro(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addPhe(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addTyr(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
        cNode *addTrp(cNode *parentC, std::vector<double*> params, std::vector<double*> params_grad);
};

#endif