#!/usr/bin/env sh

# Minimal Gradle wrapper launcher
DIR="$(cd "$(dirname "$0")" && pwd)"

# Use project-local Gradle home if none is set.
if [ -z "$GRADLE_USER_HOME" ]; then
  GRADLE_USER_HOME="$DIR/.gradle-user-home"
  export GRADLE_USER_HOME
fi

if [ -n "$JAVA_HOME" ] && [ -x "$JAVA_HOME/bin/java" ]; then
  JAVA_CMD="$JAVA_HOME/bin/java"
else
  JAVA_CMD="java"
fi

exec "$JAVA_CMD" -classpath "$DIR/gradle/wrapper/gradle-wrapper.jar" org.gradle.wrapper.GradleWrapperMain "$@"
