# HW1

## Build and run with Gradle wrapper

Use the wrapper so everyone runs the same Gradle version:

```bash
./gradlew -v
```

Notes:
- The wrapper files (`gradlew`, `gradlew.bat`, `gradle/wrapper/*`) are included in the repo and should be included in any submission zip.
- This project uses a local Gradle home (`.gradle-user-home/`) to avoid native library issues on this machine. It is a cache only and should not be committed or included in submissions.
