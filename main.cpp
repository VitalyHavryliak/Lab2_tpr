#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

#define n 5
using namespace std;

class Relation {
public:
    int s;
    //lab1
    virtual void print() {};
    virtual void operator& (Relation const &obj) {};    // Intersection
    virtual void operator| (Relation const &obj) {};    // Union
    virtual void operator> (Relation const &obj) {};    // Difference
    virtual void operator- (Relation const &obj) {};    // Symmetric Difference
    virtual void operator* (Relation const &obj) {};    // Composition
    virtual void operator^ (Relation const &obj) {};    // Include
    virtual void operator= (Relation const &obj) {};    // Set
    virtual void operator++ () {};                        // Inversion
    virtual void operator! () {};                        // !P

    //lab2
    virtual bool Reflectivity() { return false; };
    virtual bool AntiReflectivity() { return false; };
    virtual bool Symmetry() { return false; };
    virtual bool Asymetry() { return false; };
    virtual bool AntiSymetry() { return false; };
    virtual bool Transitivity() { return false; };
    virtual bool Acyclicity() { return false; };
    virtual bool Linearity() { return false; };

    virtual bool Tolerance() { return false; };
    virtual bool Equivalency() { return false; };
    virtual bool QuaziOrder() { return false; };
    virtual bool Order() { return false; };
    virtual bool StrictOrder() { return false; };
    virtual bool LinearOrder() { return false; };

    virtual void Reachability() {  };
    virtual void MutualReachability() {  };

    Relation() {}
    ~Relation() {}
};

class RelationMatrix : public Relation
{
public:
    bool **arr;
    const static int s = n;

    void describe() {
        cout << "Reflectivity: " << this->Reflectivity() << endl;
        cout << "AntiReflectivity: " << this->AntiReflectivity() << endl;
        cout << "Symmetry: " << this->Symmetry() << endl;
        cout << "Asymetry: " << this->Asymetry() << endl;
        cout << "AntiSymetry: " << this->AntiSymetry() << endl;
        cout << "Acyclicity: " << this->Acyclicity() << endl;
        cout << "Linearity: " << this->Linearity() << endl;
        cout << "Tolerance: " << this->Tolerance() << endl;
        cout << "Equivalency: " << this->Equivalency() << endl;
        cout << "QuaziOrder: " << this->QuaziOrder() << endl;
        cout << "Order: " << this->Order() << endl;
        cout << "StrictOrder: " << this->StrictOrder() << endl;
        cout << "LinearOrder: " << this->LinearOrder() << endl;
        cout << "Transitivity: " << this->Transitivity() << endl << endl;

    }

    void print() {
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    };

    void operator& (RelationMatrix const &obj) {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = obj.arr[i][j] & arr[i][j];
            }
        }
    }; // Intersection

    void operator| (RelationMatrix const &obj)
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = obj.arr[i][j] | arr[i][j];
            }
        }
    };    // Union

    void operator> (RelationMatrix const &obj)
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = arr[i][j] > obj.arr[i][j];
            }
        }
    };    // Difference

    void operator- (RelationMatrix const &obj)
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = (arr[i][j] > obj.arr[i][j]) | (obj.arr[i][j] > arr[i][j]);
            }
        }
    };    // Symmetric Difference

    void operator* (RelationMatrix const &obj)
    {
        bool **tmp;
        tmp = new bool*[s];
        for (int i = 0; i < s; i++)
        {
            tmp[i] = new bool[s];
        }

        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                tmp[i][j] = 0;
                for (int k = 0; k < s; k++)
                {
                    //tmp[i][j] = tmp[i][j] || (obj.arr[i][k] && arr[k][j]);
                    tmp[i][j] = tmp[i][j] || (arr[i][k] && obj.arr[k][j]);
                }
            }
        }

        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = tmp[i][j];
            }
        }
    };    // Composition

    bool operator^ (RelationMatrix const &obj) // Include
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                if ((arr[i][j] != obj.arr[i][j]) && arr[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    };

    void operator++ () // Inverse
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < i; j++)
            {
                swap(arr[i][j], arr[j][i]);
            }
        }
    };

    void operator! () // P_
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = !arr[i][j];
            }
        }
    };

    void operator= (const RelationMatrix& M)
    {
        arr = new bool*[s];

        for (int i = 0; i < s; i++)
            arr[i] = new bool[s];

        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = M.arr[i][j];
            }
        }
    }

    void decrease(int const obj[], bool **res, int size) // Decrease (zv)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                res[i][j] = arr[obj[i]][obj[j]];
            }
        }
    };

    void Pd() // PD
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = !arr[i][j];
            }
        }

        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < i; j++)
            {
                swap(arr[i][j], arr[j][i]);
            }
        }
    };


    bool Reflectivity() {
        for (int i = 0; i < s; i++) {
            if (!arr[i][i]) {
                return false;
            }
        }
        return true;
    };

    bool AntiReflectivity() {
        for (int i = 0; i < s; i++) {
            if (arr[i][i]) {
                return false;
            }
        }
        return true;
    };

    bool Symmetry() {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                if (arr[i][j] != arr[j][i])
                    return false;
            }
        }
        return true;
    };

    bool Asymetry() {
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                if ((arr[i][j] && arr[j][i] && i != j) || (arr[i][i]))
                    return false;
            }
        }
        return true;
    };

    bool AntiSymetry() {
        RelationMatrix m1, m2, E('d');
        m1 = *this;
        m2 = *this;
        ++m2;
        m1&m2;
        return E ^ m1;
    };

    bool Transitivity() {
        RelationMatrix E1, E2;
        E1 = *this;
        E2 = *this;
        E1*E2;
        if (*this ^ E1)
            return true;
        return false;
    };

    bool Acyclicity() {
        RelationMatrix E, tmp;
        E = *this;
        tmp = *this;
        ++tmp;
        for (int i = 0; i < s; i++) {
            E*(*this);
        }


        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                if (E.arr[i][j] & tmp.arr[i][j])
                    return false;
            }
        }
        return true;
    };

    bool Linearity() {
        /*RelationMatrix U('1'), E('d'), tmp1, tmp2;
        tmp1 = *this;
        tmp2 = *this;
        ++tmp2;
        tmp1*tmp2;
        tmp1 - E;
        U - E;
        for (int i = 0; i < s; i++)
        {
        for (int j = 0; j < s; j++)
        {
        if (tmp1.arr[i][j] != U.arr[i][j])
        return false;
        }
        }
        return true; */
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                if (!(arr[i][j] || arr[j][i]))
                    return false;
            }
        }
        return true;
    };

    bool Tolerance() {
        if (this->Reflectivity() && this->Symmetry())
            return true;
        return false;
    };

    bool Equivalency() {
        if (this->Reflectivity() && this->Symmetry() && this->Transitivity())
            return true;
        return false;
    };

    bool QuaziOrder() {
        if (this->Reflectivity() && this->Transitivity())
            return true;
        return false;
    };

    bool Order() {
        if (this->Reflectivity() && this->Transitivity() && this->AntiSymetry())
            return true;
        return false;
    };

    bool StrictOrder() {
        if (this->AntiSymetry() && this->Transitivity())
            return true;
        return false;
    };

    bool LinearOrder() {
        if (this->Reflectivity() && this->AntiSymetry() && this->Transitivity() && this->Linearity())
            return true;
        return false;
    };

    /////////////////////////////

    void SymetricComponent() {
        RelationMatrix tmp;
        tmp = *this;
        ++tmp;
        *this&tmp;
    };

    void AsymetricComponent() {
        RelationMatrix m1, m2;
        m1 = *this;
        m2 = *this;
        ++m1;
        m1&m2;
        *this - m1;
    };

    void TransistiveLock(RelationMatrix &result) {
        RelationMatrix E, tmp;
        E = *this;
        tmp = *this;
        for (int i = 1; i < s; i++) {
            tmp*(*this);
            E | tmp;
        }
        result = E;
    };

    void Reachability() {
        RelationMatrix E('d'), tmp0, tmp;
        *this;
        tmp0 = *this;
        tmp = *this;
        for (int i = 0; i < s; i++) {
            tmp*tmp0;
            *this | tmp;
        }
        *this | E;
    };

    void MutualReachability() {
        this->Reachability();
        RelationMatrix E;
        E = *this;
        ++E;
        *this&E;
        this->print();
    };

    void Factorisation() {
        this->MutualReachability();
        bool **fac;
        fac = new bool*[3];
        for (int i = 0; i < 3; i++)
        {
            fac[i] = new bool[3];
            memset(arr[i], 0, 3 * sizeof(bool));
        }


        for (int i = 0; i < 3; i++) {

            if (arr[0][i] || arr[1][i]) {
                fac[0][i] = 1;
            }
            else
            {
                fac[0][i] = 0;
            }
            fac[1][i] = arr[2][i];

            if (arr[3][i] || arr[4][i]) {
                fac[2][i] = 1;
            }
            else
            {
                fac[2][i] = 0;
            }
        }

        cout << "Factorised:" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << fac[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    RelationMatrix(char rel_type = 'e') {
        /*
        e - empty
        1 - full
        d - diagonal
        a - anti_diagonal
        */
        arr = new bool*[s];
        for (int i = 0; i < s; i++)
        {
            arr[i] = new bool[s];
            memset(arr[i], 0, s * sizeof(bool));
        }

        switch (rel_type)
        {
            case '1': {
                for (int i = 0; i < s; i++)
                {
                    for (int j = 0; j < s; j++)
                    {
                        arr[i][j] = 1;
                    }
                }
                break;
            }
            case 'd': {
                for (int i = 0; i < s; i++)
                {
                    arr[i][i] = 1;
                }
                break;
            }
            case 'a': {
                for (int i = 0; i < s; i++)
                {
                    for (int j = 0; j < s; j++)
                    {
                        arr[i][j] = (i != j);
                    }
                }
                break;
            }
            default:

                break;
        }

    }
    RelationMatrix(int **matr) {
        arr = new bool*[s];

        for (int i = 0; i < s; i++)
            arr[i] = new bool[s];

        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = matr[i][j];
            }
        }
    }
    RelationMatrix(int matr[s][s]) {
        arr = new bool*[s];

        for (int i = 0; i < s; i++)
            arr[i] = new bool[s];

        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                arr[i][j] = matr[i][j];
            }
        }
    }
    ~RelationMatrix() {}
};

int main()
{
    int P[RelationMatrix::s][RelationMatrix::s] =
            { { 0,0,1,0,0 },
              { 0,0,1,0,0 },
              { 1,0,0,1,0 },
              { 0,0,1,1,0 },
              { 1,0,0,0,0 } };

    int Q[RelationMatrix::s][RelationMatrix::s] =
            { { 0,1,0,0,0 },
              { 0,1,0,0,0 },
              { 0,0,1,0,0 },
              { 0,1,0,0,1 },
              { 1,1,0,0,0 } };

    int R[RelationMatrix::s][RelationMatrix::s] =
            { { 0,0,0,1,0 },
              { 0,1,1,0,0 },
              { 0,1,0,0,1 },
              { 0,0,0,1,0 },
              { 1,0,1,0,0 } };

    RelationMatrix p(P);
    RelationMatrix q(Q);
    RelationMatrix r(R);

    q.print();
    q.describe();
    if (!(q.Transitivity())) {
        RelationMatrix qt(Q);
        q.TransistiveLock(qt);
        qt.print();
        cout << "Qt (T-locked):" << endl;
        qt.describe();
    }

    p.Factorisation();
    return 0;
}