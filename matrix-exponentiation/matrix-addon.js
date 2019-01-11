var addon = require('bindings')('matrix-addon.node')

const n = 200;
const p = 100000;
const M = []
for (let i = 0; i < n; i++) {
    M.push([]);
    for (let j = 0; j < n; j++) {
        M[i].push(i+j+i*j);
    }
}

console.time("Matrix Multiplication Addon");
const mulResult = addon.multiply(M, M);
console.timeEnd("Matrix Multiplication Addon");

console.time("Matrix Exponentiation Addon");
const powResult = addon.power(M, p);
console.timeEnd("Matrix Exponentiation Addon");
