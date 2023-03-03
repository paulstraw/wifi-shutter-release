const char indexHtml[] PROGMEM = R"(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1">

    <title>Remote Shutter</title>

    <style>
      html, body {
        height: 100%;
      }

      body, button {
          font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";
      }

      body {
        display: flex;
        flex-direction: column;
        gap: 16px;
        justify-content: center;
        align-items: center;
      }

      button {
        font-size: 24px;
        border-radius: 6px;
        border: 6px;
        background: #334155;
        color: #fff;
        font-weight: 600;
        padding: 12px;
        width: 300px;
      }

      [disabled] {
        opacity: 0.5;
      }

      .loading:after {
        content: "…"
      }
    </style>
  </head>

  <body>
    <button id="focus">Focus</button>
    <button id="shutter">Shutter</button>

    <script>
      (() => {
        const focusButton = document.querySelector('#focus')
        const shutterButton = document.querySelector('#shutter')

        const handleClick = async (e) => {
          e.target.classList.add('loading')

          focusButton.disabled = true;
          shutterButton.disabled = true;

          try {
            await fetch(`/${e.target.id}`, {
              method: 'POST',
            })
          } catch (err) {
            alert(err)
          } finally {
            e.target.classList.remove('loading')

            focusButton.disabled = false;
            shutterButton.disabled = false;
          }
        }

        focusButton.addEventListener('click', handleClick)
        shutterButton.addEventListener('click', handleClick)
      })()
    </script>
  </body>
</html>
)";
