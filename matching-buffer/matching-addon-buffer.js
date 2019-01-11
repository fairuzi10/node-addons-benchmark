const addon = require('bindings')('matching-addon-buffer.node')

const n = 50000000;
const m = 1000000;

const aAscii = 'a'.charCodeAt(0);
let az = "";
for (let i = 0; i < 26; i++) {
    az += String.fromCharCode(i + aAscii);
}

const str = Buffer.alloc(n, az);
const pattern = Buffer.alloc(m, az);

console.time("Matching Addon Buffer");
const result = addon.countOccurrence(str, pattern);
console.timeEnd("Matching Addon Buffer");

