#lang at-exp racket
(require scribble/text)
(provide make-directory/remove make-directory/ignore url for/nl header cpp-wrap)

(define (make-directory/remove dir)
  (when (directory-exists? dir)
    (delete-directory/files dir))
  (make-directory dir))

(define (make-directory/ignore dir)
  (unless (directory-exists? dir)
    (make-directory dir)))

(define url "https://bitbucket.org/LoEE/lpc1xxx-hw/")

(define-syntax-rule (for/nl args ...) (add-newlines (for/list args ...)))
(define-syntax-rule (for*/nl args ...) (add-newlines (for*/list args ...)))

(define (header url . body)
  @list{
/*
@add-prefix["   "]{@body}
 
   This is an automatically generated file. For more details see:
       @url
    
   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/})

(define (cpp-wrap name . body)
  @list{
#ifndef @|name|_H
#define @|name|_H

@body

#endif // @|name|_H
})
