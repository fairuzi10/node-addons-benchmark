const addon = require('bindings')('set');

const n = 7500000;
const set = new addon.Set();

console.time("Set Addon");
for (let i = 0; i < n; i++) {
    set.add(i);
}
for (let i = 0; i < n; i++) {
    set.has(i);
}
for (let i = 0; i < n; i++) {
    set.delete(i);
}
console.timeEnd("Set Addon");
