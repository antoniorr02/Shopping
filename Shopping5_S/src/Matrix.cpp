/* 
 * File:   matrix.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */


#include "Matrix.h"
#include <fstream>
#include <assert.h>
#include <iomanip>

using namespace std;

/**
 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
 * It is assumed that org and dest have the memory properly allocated 
 * @param dest destination matrix
 * @param org  source matrix
 * @param nrows number of rows
 * @param ncols number of cols
 */
void copy(double **dest, double **org, size_t nrows, size_t ncols) {
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            dest[i][j] = org[i][j];
            // NOTA: orig es un double **: entonces orig[i] double * orig[i][j] es double **
        }
    }
}

/** 
 * @brief this method reserve memory to allocate a 2D matrix of size r x c.
 * @param r number of rows
 * @param c number of cols
 * @return the pointer to the memory block containing the data
 */
double ** allocate(size_t r, size_t c) {
    double ** block;
    // allocate memory into block
    block = new double * [r];
    for (int i = 0; i < r; i++) {
        block[i] = new double [c];
    }
    return block;
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()==p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;

    bool enc = false;
    for (int i = 0; i < idx.size() && !enc; i++) {
        if (idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            enc = true;
        }
    }
    return salida;
}

void Matrix::deallocate() {
    if (_data != nullptr) {
        for (int i = 0; i < _nrows; i++) {
            delete[] _data[i];
            _data[i] = nullptr;
        }
        delete[] _data;
    }
    _data = nullptr;
}

Matrix::Matrix() {
    _nrows = 0;
    _ncols = 0;
    _data = nullptr;
}

void Matrix::setValues(double valor) {
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            _data[i][j] = valor;
        }
    }
}

Matrix::Matrix(size_t f, size_t c, double vdef) {
    _data = allocate(f, c);
    _nrows = f;
    _ncols = c;
    setValues(vdef);
}

Matrix::Matrix(const Matrix& orig) {
    _data = allocate(orig._nrows, orig._ncols);
    _nrows = orig._nrows;
    _ncols = orig._ncols;
    _rowLabels = orig._rowLabels;
    _colLabels = orig._rowLabels;
    copy(_data, orig._data, _nrows, _ncols);
}

Matrix::Matrix(const std::string *rowLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double value) {
    _data = allocate(nrows, ncols);
    _nrows = nrows;
    _ncols = ncols;
    setValues(value);

    setLabels(_rowLabels, rowLabels, nrows);
    setLabels(_colLabels, colsLabels, ncols);

    if (_rowLabels.isEmpty() || _colLabels.isEmpty()) {
        clear();
    }
}

std::string Matrix::labelAtRow(size_t row) const {
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const {
    return labelWithValuePosInIndex(_colLabels, col);
}

void Matrix::resize(size_t nrows, size_t ncols, double defValue) {

    deallocate();
    _nrows = nrows;
    _ncols = ncols;
    _data = allocate(_nrows, _ncols); // Reservo memoria
    setValues(defValue); // Meto los valores por defecto.

}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    if (nrows < 1 || ncols < 1) {
        clear(); // En caso de error Matriz por defecto
    } else {
        resize(nrows, ncols, value);
        setLabels(_rowLabels, rowLabels, nrows);
        setLabels(_colLabels, colLabels, ncols);
    }
}

void Matrix::clear() {
    _nrows = 0;
    _ncols = 0;
    deallocate();
}

Matrix::~Matrix() {
    clear();
}

double & Matrix::at(size_t f, size_t c) {
    assert(f < _nrows && c < _ncols);
    return _data[f][c];
}

const double & Matrix::at(size_t f, size_t c) const {
    assert(f < _nrows && c < _ncols);
    return _data[f][c];
}

double & Matrix::operator()(size_t f, size_t c) {
    return at(f, c);
}

const double & Matrix::operator()(size_t f, size_t c) const {
    return at(f, c);
}

int Matrix::rowIndexOf(const std::string & label) const {
    int pos = _nrows;
    for (int i = 0; i < _nrows; i++) {
        if (label == _rowLabels.at(i).getKey()) {
            pos = i;
            i = _nrows;
        }
    }
    return pos;
}

int Matrix::colIndexOf(const std::string & label) const {
    int pos = _ncols;
    for (int i = 0; i < _ncols; i++) {
        if (label == _colLabels.at(i).getKey()) {
            pos = i;
            i = _ncols;
        }
    }
    return pos;
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel) {
    return _data[rowIndexOf(rowLabel)][colIndexOf(colLabel)];
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel) {
    return at(rowLabel, colLabel);
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const {
    return _data[rowIndexOf(rowLabel)][colIndexOf(colLabel)];
}

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const {
    return at(rowLabel, colLabel);
}

ostream & operator<<(ostream & flujo, const Matrix& m) {
    flujo << m._nrows << " " << m._ncols << endl;
    flujo << setw(7) << std::right << "|";
    for (int i = 0; i < m._colLabels.size(); i++)
        flujo << setw(7) << std::right << m._colLabels.at(i).getKey();
    flujo << endl;

    for (int i = 0; i < m._nrows; i++) {
        if (m._rowLabels.size() > 0)
            flujo << setw(7) << std::right << m._rowLabels.at(i).getKey();
        for (int j = 0; j < m._ncols; j++) {
            flujo << setw(7) << setprecision(2) << std::right << m._data[i][j] << " ";
        }
        flujo << endl;
    }
    return flujo;
//     for (int i = 0; i < m._nrows; i++) {
//         for (int j = 0; j < m._ncols; j++) {
//             flujo << m._data[i][j] << " ";
//         }
//         flujo << endl;
//     }
     
}

Matrix & Matrix::operator=(const Matrix& m) {
    clear();
    _nrows = m._nrows;
    _ncols = m._ncols;
    _rowLabels = m._rowLabels;
    _colLabels = m._colLabels;
    _data = allocate(_nrows, _ncols);
    copy(_data, m._data, _nrows, _ncols);
    return * this;
}

void Matrix::setLabels(Index & idx, const string * labels, int nlabels) {
    idx.clear();
    int lb, ub;
    bool correct = true;
    for (int i = 0; i < nlabels && correct; i++) {
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb == ub) { // it is NOT in the set
            idx.add(Pair(labels[i], i));
        } else {
            correct = false;
        }
    }
    if (!correct) idx.clear();
}

int Matrix::getLabels(const Index & idx, string * labels) const {
    if (idx.size() > 0) {
        for (int i = 0; i < idx.size(); i++) {
            labels[i] = idx.at(i).getKey(); // Guardamos las etiquetas en el vector destino labels. 
        }
    }
    return idx.size();
}

int Matrix::getRowLabels(string * labels) const {
    return getLabels(_rowLabels, labels);
}

int Matrix::getColLabels(string *labels) const {
    return getLabels(_colLabels, labels);
}

size_t Matrix::columns() const {
    return _ncols;
}

size_t Matrix::rows() const {
    return _nrows;
}

void Matrix::save(const string & nf) const {
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix ";
        if (_rowLabels.size() == 0)
            fsal << "unlabeled" << endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" << endl;
}

void Matrix::load(const string & nf) {
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
        fent >> cad >> labeled;
        fent >> _nrows >> _ncols;
        if (labeled == "labeled") {
            for (int i = 0; i < _nrows; i++) {
                fent >> cad;
                _rowLabels.add(Pair(cad, i));
            }
            for (int i = 0; i < _ncols; i++) {
                fent >> cad;
                _colLabels.add(Pair(cad, i));
            }
        }
        _data = allocate(_nrows, _ncols);
        for (int i = 0; i < _nrows; i++) {
            for (int j = 0; j < _ncols; j++) {
                fent >> _data[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" << endl;
}

Matrix & Matrix::operator*=(double val) {
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            _data[i][j] *= val;
        }
    }
    return * this;
}

Matrix & Matrix::operator+=(double val) {
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            _data[i][j] += val;
        }
    }
    return * this;
}

Matrix Matrix::operator*(const Matrix & m) const {
    assert(_ncols == m._nrows);
    Matrix matriz(_nrows, m._ncols);
    double elemento = 0;

    for (int i = 0; i < _nrows; i++) {
        for (int n = 0; n < m._ncols; n++) {
            for (int j = 0; j < _ncols; j++) {
                elemento += _data[i][j] * m._data[j][n];
            }
            matriz._data[i][n] = elemento;
            elemento = 0;
        }
    }
    matriz._colLabels = _colLabels; 

    return matriz;
}

Matrix Matrix::operator+(double val) const {
    Matrix matriz;
    matriz = *this;
    //    matriz.resize(_nrows,_ncols, val);
    //    matriz._rowLabels = _rowLabels;
    //    matriz._colLabels = _colLabels; // No se si esto es necesario!!
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            matriz._data[i][j] += val/*_data[i][j]*/;
        }
    }
    return matriz;
} // El código comentado tendría la misma función que utilizar = *this.

Matrix Matrix::operator*(double val) const {
    Matrix matriz(*this);
    //    matriz.resize(_nrows, _ncols, val);
    //    matriz._rowLabels = _rowLabels;
    //    matriz._colLabels = _colLabels; 
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            matriz._data[i][j] *= val/*_data[i][j]*/;
        }
    }
    return matriz;
} // El código comentado tendría la misma función que utilizar = *this.

Matrix operator+(double ival, const Matrix & dch) {
    Matrix matriz;
    matriz = dch;
    for (int i = 0; i < dch._nrows; i++) {
        for (int j = 0; j < dch._ncols; j++) {
            matriz._data[i][j] = dch._data[i][j] + ival;
        }
    }
    return matriz;
}

Matrix operator*(double ival, const Matrix & dch) {
    Matrix matriz;
    matriz = dch;
    for (int i = 0; i < dch._nrows; i++) {
        for (int j = 0; j < dch._ncols; j++) {
            matriz._data[i][j] = dch._data[i][j] * ival;
        }
    }
    return matriz;
}

Matrix & Matrix::normalize() {
    double divisor[_nrows] = {0};
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            divisor[i] += _data[i][j];
        }
    }
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            if (divisor[i] != 0)
                _data[i][j] /= divisor[i];
            else 
                _data[i][j] = 1.0/_ncols;
        }
    }
    return * this;
}
