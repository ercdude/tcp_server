;;; tcp_server-docker.el --- Helper commands for tcp_server dev -*- lexical-binding: t -*-
;;
;; URL:
;; Author: Eric Menezes <eirc.m@protonmail.com>

(defvar compose-command-fmt
  "ssh %s 'docker-compose -f %s --project-directory %s %s'"
  "The format of the docker-compose command")

(defvar compose-build-command-fmt
  "ssh %s 'docker-compose -f %s --project-directory %s build'"
  "The format of the docker-compose command")

(defvar tcp_server-docker-host "ice"
  "The host which docker is running.")

(defvar tcp_server-project-path "~/cm/recipes/tcp_server/src/src"
  "The path of project file.")

(defvar tcp_server-compose-path (concat tcp_server-project-path
                                     "/tcp_server.compose")
  "The path of docker-compose file.")

(defvar tcp_server-dev-service "src_tcp_server_build_1"
  "The name of the development container.")

(defvar tcp_server-gen-proj-command "cmake /src -B/build"
  "The command to build the tcp_server project.")

(defvar tcp_server-make-proj-command "make -C /build"
  "The command to build the tcp_server project.")

(defvar tcp_server-container-exec-command (list "docker" "container" "exec")
  "A list as argv for executing something inside a container.")

;;;###autoload
(defun tcp_server-compose-up ()
  "Starts the composition of tcp_server"
  (interactive)
  (let ((command (format compose-command-fmt
                         tcp_server-docker-host
                         tcp_server-compose-path
                         tcp_server-project-path
                         "up -d")))
    (compile command)))

;;;###autoload
(defun tcp_server-compose-down ()
  "Starts the composition of tcp_server"
  (interactive)
  (let ((command (format compose-command-fmt
                         tcp_server-docker-host
                         tcp_server-compose-path
                         tcp_server-project-path
                         "down")))
    (compile command)))

;;;###autoload
(defun tcp_server-compose-build ()
  "Starts the composition of tcp_server"
  (interactive)
  (let ((command (format compose-build-command-fmt
                         tcp_server-docker-host
                         tcp_server-compose-path
                         tcp_server-project-path)))
    (compile command)))

(defun tcp_server-make-comint (container command)
  "Makes a comint buffer with COMMAND inside the given docker CONTAINER."
  (let ((default-directory (format "/ssh:%s:"
                                   tcp_server-docker-host))
        (program (car tcp_server-container-exec-command))
        (args (cdr tcp_server-container-exec-command)))
    (apply 'make-comint
           "tcp_server-dev"
           program
           nil
           `(,@args "-it" ,container ,command))))

(defun tcp_server-run-command (container command)
  "Runs a COMMAND inside the given docker CONTAINER."
  (let ((default-directory (format "/ssh:%s:"
                                   tcp_server-docker-host)))
    (compile (string-join `(,@tcp_server-container-exec-command
                            "-it"
                            ,container
                            ,command)
                          " "))))

;;;###autoload
(defun tcp_server-dev-shell ()
  "Starts the composition of tcp_server"
  (interactive)
  (tcp_server-make-comint tcp_server-dev-service "/bin/sh"))

;;;###autoload
(defun tcp_server-build-project ()
  "Builds the project by calling cmake and make inside the tcp_server-dev-service."
  (interactive)
  (and (tcp_server-run-command tcp_server-dev-service
                            tcp_server-gen-proj-command)
       (tcp_server-run-command tcp_server-dev-service
                            tcp_server-make-proj-command)))

