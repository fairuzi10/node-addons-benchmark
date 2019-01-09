const countOccurrence = (str, pattern) => {
    const n = str.length;
    const m = pattern.length;

    if (n < m) {
        return 0;
    }

    const base = 37;
    const mod = 10000000000037;
    let hashPattern = 0;
    for (let i = 0; i < m; i++) {
        hashPattern = (hashPattern*base + pattern.charCodeAt(i)+1) % mod;
    }

    let hashStr = 0;
    let baseLast = 1;
    for (let i = 0; i < m; i++) {
        hashStr = (hashStr*base + str.charCodeAt(i)+1) % mod;
        if (i < m-1) {
            baseLast = (baseLast*base) % mod;
        }
    }

    let ret = 0;
    if (hashStr === hashPattern) {
        ret++;
    }
    for (let i = m; i < n; i++) {
        // removing the last character
        hashStr = (hashStr - (str.charCodeAt(i-m)+1)*baseLast) % mod;
        if (hashStr < 0) {
            hashStr += mod;
        }
        hashStr = (hashStr*base + str.charCodeAt(i)+1) % mod;
        if (hashStr == hashPattern) {
            ret++;
        }
    }
    return ret;
}

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

console.time("Matching");
console.log(countOccurrence(str, pattern));
console.timeEnd("Matching");
