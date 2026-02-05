@echo off
setlocal
set DIR=%~dp0
set JAVA_CMD=java
if "%GRADLE_USER_HOME%"=="" set GRADLE_USER_HOME=%DIR%.gradle-user-home
if not "%JAVA_HOME%"=="" set JAVA_CMD=%JAVA_HOME%\bin\java
"%JAVA_CMD%" -classpath "%DIR%gradle\wrapper\gradle-wrapper.jar" org.gradle.wrapper.GradleWrapperMain %*
endlocal
