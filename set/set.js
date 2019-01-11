const n = 7500000;
const set = new Set();

console.time("Set");
for (let i = 0; i < n; i++) {
    set.add(i);
}
for (let i = 0; i < n; i++) {
    set.has(i);
}
for (let i = 0; i < n; i++) {
    set.delete(i);
}
console.timeEnd("Set");
