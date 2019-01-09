const addon = require('bindings')('matching-addon.node')

const buildStr = (len) => {
    let az = "";
    for (let i = 0; i < 26; i++) {
        az += String.fromCharCode(i + aAscii);
    }

    let ret = ""
    let i = 0;
    while (i+26 < len) {
        ret += az;
        i += 26
    }
    while (i < len) {
        ret += String.fromCharCode(i % 26 + aAscii);
        i++;
    }
    return ret
}

const n = 50000000;
const m = 1000000;

let str = "";
let pattern = "";
const aAscii = 'a'.charCodeAt(0);

str = buildStr(n);
pattern = buildStr(m);

console.time("Matching Addon");
console.log(addon.countOccurrence(str, pattern));
console.timeEnd("Matching Addon");

