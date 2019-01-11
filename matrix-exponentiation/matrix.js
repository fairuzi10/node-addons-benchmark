const MOD = 10000019;

// multiply matrix a and b, both having size nxn, in O(N^3)
const multiply = (A, B) => {
    const n = A.length;
    const result = [];
    for (let i = 0; i < n; i++) {
        result.push([]);
        for (let j = 0; j < n; j++) {
            result[i].push(0);
            for (let k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + A[i][k]*B[k][j]) % MOD;
            }
        }
    }
    return result;
}

// return M^p in O(N^3*log(p))
const power = (M, p) => {
    if (p === 1) {
        return M;
    } else if (p % 2 === 1) {
        const temp = power(M, p-1);
        return multiply(temp, M);
    } else {
        const temp = power(M, p/2);
        return multiply(temp, temp);
    }
}

const n = 200;
const p = 100000;
const M = []
for (let i = 0; i < n; i++) {
    M.push([]);
    for (let j = 0; j < n; j++) {
        M[i].push(i+j+i*j);
    }
}

console.time("Matrix Multiplication");
const mulResult = multiply(M, M);
console.timeEnd("Matrix Multiplication");

console.time("Matrix Exponentiation");
const powResult = power(M, p);
console.timeEnd("Matrix Exponentiation");
