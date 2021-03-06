/*! terminal.js v2.0   | (c) 2014 Erik Österberg | https://github.com/eosterberg/terminaljs
 *! terminal.js v2.1.2 | (c) 2018 Erik Nonhebel  | https://github.com/lleuda/shell */

var Terminal = (function () {
    // PROMPT_TYPE
    var PROMPT_INPUT = 1, PROMPT_PASSWORD = 2
    var VersionMajor = "2"
    var VersionMinor = "1.2"

    var fireCursorInterval = function (inputField, terminalObj) {
        var cursor = terminalObj._cursor
        setTimeout(function () {
            if (inputField.parentElement && terminalObj._shouldBlinkCursor) {
                cursor.style.visibility = cursor.style.visibility === 'visible' ? 'hidden' : 'visible'
                fireCursorInterval(inputField, terminalObj)
            } else {
                cursor.style.visibility = 'visible'
            }
        }, 500)
    }

    var firstPrompt = true;
    promptInput = function (terminalObj, message, PROMPT_TYPE, callback) {
        var shouldDisplayInput = (PROMPT_TYPE === PROMPT_INPUT)
        var inputField = document.createElement('input')

        inputField.style.outline = 'none'
        inputField.style.border = 'none'
        inputField.style.fontSize = '1em'
        inputField.style.fontFamily = 'Monaco, Courier'
        inputField.style.background = "gray"
        inputField.style.color = "white"

        terminalObj._inputLine.textContent = ''
        terminalObj._input.style.display = 'block'
        terminalObj._input.appendChild(inputField)

        terminalObj._dir.textContent = message.length ? message : ""

        inputField.onblur = function () {
            terminalObj._cursor.style.display = 'none'
        }

        inputField.onfocus = function () {
            inputField.value = terminalObj._inputLine.textContent
            terminalObj._cursor.style.display = 'inline'
        }

        terminalObj.html.onclick = function () {
            inputField.focus()
        }

        inputField.onkeydown = function (e) {
            //if (e.which === 37 || e.which === 39 || e.which === 38 || e.which === 40 || e.which === 9) {
            if (e.which === 38 || e.which === 40 || e.which === 9) {
                e.preventDefault()
            } else if (shouldDisplayInput && e.which !== 13) {
                setTimeout(function () {
                    terminalObj._inputLine.textContent = inputField.value
                }, 1)
            }
        }
        inputField.onkeyup = function (e) {
            if (e.which === 13) {
                terminalObj._input.style.display = 'none'
                var inputValue = inputField.value

                if (shouldDisplayInput) terminalObj.print(message + inputValue)

                //terminalObj.html.removeChild(inputField)
                terminalObj._input.removeChild(inputField)

                if (typeof(callback) === 'function') callback(inputValue)
            }
        }
        if (firstPrompt) {
            firstPrompt = false
            setTimeout(function () { inputField.focus() }, 50)
        } else {
            inputField.focus()
        }
    }

    var terminalBeep

    var TerminalConstructor = function (id) {

        this.html = document.createElement('div')
        this.html.className = 'Terminal'
        if (typeof(id) === 'string') { this.html.id = id }

        this._innerWindow = document.createElement('div')
        this._output = document.createElement('p')
        this._dir = document.createElement('span')
        this._inputLine = document.createElement('span') //the span element where the users input is put
        this._cursor = document.createElement('span')
        this._input = document.createElement('p') //the full element administering the user input, including cursor

        this.print = function (message) {
            var newLine = document.createElement('div')
            newLine.textContent = message
            this._output.appendChild(newLine)
        }

        this.input = function (message, callback) {
            promptInput(this, message, PROMPT_INPUT, callback)
        }

        this.password = function (message, callback) {
            promptInput(this, message, PROMPT_PASSWORD, callback)
        }

        this.clear = function () {
            this._output.innerHTML = ''
        }

        this.version = function () {
            return VersionMajor + "." + VersionMinor
        }

        this.sleep = function (milliseconds, callback) {
            setTimeout(callback, milliseconds)
        }

        this.setTextSize = function (size) {
            this._output.style.fontSize = size
            this._input.style.fontSize = size
        }

        this.setTextColor = function (col) {
            this.html.style.color = col
            this._cursor.style.background = col
        }

        this.setBackgroundColor = function (col) {
            this.html.style.background = col
        }

        this.setWidth = function (width) {
            this.html.style.width = width
        }

        this.setHeight = function (height) {
            this.html.style.height = height
        }

        this._input.appendChild(this._dir)
        this._innerWindow.appendChild(this._output)
        this._innerWindow.appendChild(this._input)
        this.html.appendChild(this._innerWindow)

        this.setBackgroundColor('black')
        //this.setBackgroundColor('red')
        this.setTextColor('white')
        this.setTextSize('1em')
        this.setWidth('100%')
        this.setHeight('100%')

        this.html.style.fontFamily = 'Monaco, Courier'
        this.html.style.margin = '0'
        this._innerWindow.style.padding = '10px'
        this._input.style.margin = '0'
        this._output.style.margin = '0'
        this._input.style.display = 'none'
    }

    return TerminalConstructor
}())
