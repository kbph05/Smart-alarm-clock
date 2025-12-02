import fs from 'fs';

const CACHE_FILE = './cache.json';

export function loadCache() {
    if (!fs.existsSync(CACHE_FILE)) {
        return {
            lastWeatherFetch: null,
            lastCalendarFetch: null
        };
    }
    return JSON.parse(fs.readFileSync(CACHE_FILE, 'utf-8'));
}

export function saveCache(cache) {
    fs.writeFileSync(CACHE_FILE, JSON.stringify(cache, null, 2));
}



export function getCache() {
    return loadCache();   // always returns the latest version on disk
}

export function wasFetchedToday(cacheKey) {
    const cache = getCache();
    const timestamp = cache[cacheKey];

    if (!timestamp) return false;

    const last = new Date(timestamp);
    const now  = new Date();

    return last.toDateString() === now.toDateString();
}

export function updateCacheTimestamp(cacheKey) {
    const cache = getCache();
    cache[cacheKey] = new Date().toISOString();
    saveCache(cache);
}