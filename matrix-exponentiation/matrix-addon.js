var addon = require('bindings')('matrix-addon.node')

const n = 200;
const p = 100000;
const m = []
for (let i = 0; i < n; i++) {
    m.push([]);
    for (let j = 0; j < n; j++) {
        m[i].push(i+j+i*j);
    }
}

console.time("Matrix Addon");
const result = addon.power(m, p);
console.timeEnd("Matrix Addon");
