export default async function handler(req, res) {
  if (req.method !== "POST") {
    return res.status(405).json({ message: "Method not allowed" })
  }

  const { email } = req.body

  if (!email || !email.includes("@")) {
    return res.status(400).json({ message: "E-mail inválido" })
  }

  try {
    // Here you would typically:
    // 1. Validate the email
    // 2. Store it in a database
    // 3. Set up email alert system

    console.log("Email cadastrado para alertas:", email)

    // Simulate storing in database
    // await database.collection('alert_emails').add({ email, createdAt: new Date() });

    res.status(200).json({
      message: "E-mail cadastrado com sucesso!",
      email: email,
    })
  } catch (error) {
    console.error("Erro ao cadastrar e-mail:", error)
    res.status(500).json({ message: "Erro interno do servidor" })
  }
}
