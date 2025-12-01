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
