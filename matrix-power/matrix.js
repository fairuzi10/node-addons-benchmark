const MOD = 10000019;

// multiply matrix a and b, both having size nxn
const multiply = (a, b) => {
    const n = a.length;
    const result = [];
    for (let i = 0; i < n; i++) {
        result.push([]);
        for (let j = 0; j < n; j++) {
            result[i].push(0);
            for (let k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + a[i][k]*b[k][j]) % MOD;
            }
        }
    }
    return result;
}

const power = (m, p) => {
    if (p === 1) {
        return m;
    } else if (p % 2 === 1) {
        const temp = power(m, p-1);
        return multiply(temp, m);
    } else {
        const temp = power(m, p/2);
        return multiply(temp, temp);
    }
}

const n = 200;
const p = 100000;
const m = []
for (let i = 0; i < n; i++) {
    m.push([]);
    for (let j = 0; j < n; j++) {
        m[i].push(i+j+i*j);
    }
}

console.time("Matrix");
const result = power(m, p);
console.timeEnd("Matrix");
